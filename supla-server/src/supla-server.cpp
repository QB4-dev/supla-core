/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <curl/curl.h>
#include <openssl/ssl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/resource.h>

#include "accept_loop.h"
#include "asynctask/asynctask_default_thread_pool.h"
#include "asynctask/asynctask_queue.h"
#include "asynctask/voice_assistant_sync_thread_pool.h"
#include "cyclictasks/agent.h"
#include "db/database.h"
#include "http/asynctask_http_thread_pool.h"
#include "http/remote_gateway_access_token_provider.h"
#include "ipc/ipcsocket.h"
#include "lck.h"
#include "log.h"
#include "mqtt_client_suite.h"
#include "proto.h"
#include "push/pn_delivery_task_thread_pool.h"
#include "serverstatus.h"
#include "srpc/srpc.h"
#include "sthread.h"
#include "supla-socket.h"
#include "svrcfg.h"
#include "tools.h"
#include "user.h"

int main(int argc, char *argv[]) {
#if __DEBUG
// We give up capturing critical signals in favor of coredump.
// st_hook_critical_signals();
#endif

  void *ssd_ssl = nullptr;
  void *ssd_tcp = nullptr;
  void *ipc = nullptr;
  void *tcp_accept_loop_thread = nullptr;
  void *ssl_accept_loop_thread = nullptr;
  void *ipc_accept_loop_thread = nullptr;
  supla_cyclictasks_agent *cyclictasks_agent = nullptr;

  SSL_library_init();
  SSL_load_error_strings();
  curl_global_init(CURL_GLOBAL_ALL);

  // INIT BLOCK
  if (svrcfg_init(argc, argv) == 0) return EXIT_FAILURE;

#if defined(__DEBUG) && __SSOCKET_WRITE_TO_FILE == 1
  unlink("ssocket_read.raw");
  unlink("ssocket_write.raw");
#endif /* defined(__DEBUG) && __SSOCKET_WRITE_TO_FILE == 1 */

  {
    char dt[64];

    supla_log(LOG_INFO, "Server version %s [Protocol v%i]", SERVER_VERSION,
              SUPLA_PROTO_VERSION);

    supla_log(LOG_INFO, "Started at %s", st_get_datetime_str(dt));
  }

  if (run_as_daemon && 0 == st_try_fork()) {
    goto exit_fail;
  }

  if (database::mainthread_init() == false) {
    goto exit_fail;
  }

  {
    database *db = new database();
    if (!db->check_db_version(DB_VERSION, 60)) {
      delete db;
      database::mainthread_end();
      goto exit_fail;
    } else {
      delete db;
    }
  }

  // Start service only when the server configuration is already loaded.
  supla_remote_gateway_access_token_provider::global_instance()
      ->start_service();

  supla_log(LOG_INFO, "SSL version: %s", OpenSSL_version(OPENSSL_VERSION));

  if (scfg_bool(CFG_SSL_ENABLED) == 1) {
    if (0 == (ssd_ssl = ssocket_server_init(scfg_string(CFG_SSL_CERT),
                                            scfg_string(CFG_SSL_KEY),
                                            scfg_int(CFG_SSL_PORT), 1)) ||
        0 == ssocket_openlistener(ssd_ssl)) {
      goto exit_fail;
    }
  }

  if (scfg_bool(CFG_TCP_ENABLED) == 1) {
    if (0 == (ssd_tcp =
                  ssocket_server_init("", "", scfg_int(CFG_TCP_PORT), 0)) ||
        0 == ssocket_openlistener(ssd_tcp)) {
      goto exit_fail;
    }
  }

  if (0 == st_set_ug_id(scfg_getuid(CFG_UID), scfg_getgid(CFG_GID))) {
    goto exit_fail;
  }

#if __DEBUG
  prctl(PR_SET_DUMPABLE, 1);
#endif /*__DEBUG*/

  // ASYNCTASK QUEUE
  supla_asynctask_queue::global_instance();
  supla_asynctask_default_thread_pool::global_instance();
  supla_voice_assistant_sync_thread_pool::global_instance();
  supla_asynctask_http_thread_pool::global_instance();
  supla_pn_delivery_task_thread_pool::global_instance();

  supla_user::init();
  supla_connection::init();

  st_setpidfile(pidfile_path);
  st_mainloop_init();
  st_hook_signals();

  ipc = ipcsocket_init(scfg_string(CFG_IPC_SOCKET_PATH));

  // INI ACCEPT LOOP

  if (ssd_ssl != NULL)
    sthread_simple_run(accept_loop, ssd_ssl, 0, &ssl_accept_loop_thread);

  if (ssd_tcp != NULL)
    sthread_simple_run(accept_loop, ssd_tcp, 0, &tcp_accept_loop_thread);

  if (ipc) sthread_simple_run(ipc_accept_loop, ipc, 0, &ipc_accept_loop_thread);

  // CYCLIC TASKS
  cyclictasks_agent = new supla_cyclictasks_agent();

  // MQTT
  supla_mqtt_client_suite::globalInstance()->start();

  // MAIN LOOP
  while (st_app_terminate == 0) {
    st_mainloop_wait(1000000);
    serverstatus::globalInstance()->mainLoopHeartbeat();
    supla_connection::log_limits();
    supla_user::log_metrics(3600);
    supla_asynctask_queue::global_instance()->log_stuck_warning();
  }

  supla_log(LOG_INFO, "Shutting down...");

  // RELEASE BLOCK

  if (ipc != NULL) {
    ipcsocket_close(ipc);
    sthread_twf(ipc_accept_loop_thread, true);  // ! after ipcsocket_close and
                                                // before ipcsocket_free !
    ipcsocket_free(ipc);
  }

  if (ssd_ssl != NULL) {
    ssocket_close(ssd_ssl);
    sthread_twf(ssl_accept_loop_thread, true);  // ! after ssocket_close and
                                                // before ssocket_free !
    ssocket_free(ssd_ssl);
  }

  if (ssd_tcp != NULL) {
    ssocket_close(ssd_tcp);
    sthread_twf(tcp_accept_loop_thread, true);  // ! after ssocket_close and
                                                // before ssocket_free !
    ssocket_free(ssd_tcp);
  }

  delete cyclictasks_agent;

  supla_asynctask_queue::global_instance_release();  // before
                                                     // serverconnection_free()

  supla_connection::cleanup();

  // ! after serverconnection_free() and before user_free()
  supla_mqtt_client_suite::globalInstanceRelease();
  // -----------------------------------------------

  supla_remote_gateway_access_token_provider::global_instance()
      ->stop_service();  // Stop the service before calling
                         // curl_global_cleanup()

  supla_user::user_free();
  database::mainthread_end();

  st_mainloop_free();  // Almost at the end
  st_delpidfile(pidfile_path);
  svrcfg_free();
  curl_global_cleanup();

  {
    char dt[64];
    supla_log(LOG_INFO, "Stopped at %s", st_get_datetime_str(dt));
  }

  return EXIT_SUCCESS;

exit_fail:

  ssocket_free(ssd_ssl);
  ssocket_free(ssd_tcp);
  svrcfg_free();
  curl_global_cleanup();

  exit(EXIT_FAILURE);
}
