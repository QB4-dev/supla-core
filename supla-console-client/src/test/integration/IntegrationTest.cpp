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

#include "IntegrationTest.h"

#include "MySqlShell.h"
#include "log.h"
#include "tools.h"

namespace testing {

using std::string;

char *IntegrationTest::sqlDir = NULL;
char IntegrationTest::defaultDbName[] = "supla_test";
char IntegrationTest::defaultDbHost[] = "db";
char IntegrationTest::defaultDbUser[] = "supla";
char *IntegrationTest::dbName = IntegrationTest::defaultDbName;
char *IntegrationTest::dbHost = IntegrationTest::defaultDbHost;
char *IntegrationTest::dbUser = IntegrationTest::defaultDbUser;

void integration_test_on_getversion_result(void *_suplaclient, void *instance,
                                           TSDC_SuplaGetVersionResult *result) {
  static_cast<IntegrationTest *>(instance)->onGetVersionResult(result);
}

void integration_test_on_connected(void *_suplaclient, void *instance) {
  static_cast<IntegrationTest *>(instance)->onConnected();
}

void integration_test_on_disconnected(void *_suplaclient, void *instance) {
  static_cast<IntegrationTest *>(instance)->onDisconnected();
}

void integration_test_on_connerror(void *_suplaclient, void *instance,
                                   int code) {
  static_cast<IntegrationTest *>(instance)->onConnectionError(code);
}

void integration_test_on_registered(void *_suplaclient, void *instance,
                                    TSC_SuplaRegisterClientResult_D *result) {
  static_cast<IntegrationTest *>(instance)->onRegistered(result);
}

void integration_test_on_registererror(void *_suplaclient, void *instance,
                                       int code) {
  static_cast<IntegrationTest *>(instance)->onRegistrationError(code);
}

void integration_test_on_superuser_authorization_result(void *_suplaclient,
                                                        void *instance,
                                                        char authorized,
                                                        _supla_int_t code) {
  static_cast<IntegrationTest *>(instance)->onSuperuserAuthorizationResult(
      authorized, code);
}

void integration_test_on_channel_function_set_result(
    void *_suplaclient, void *instance, TSC_SetChannelFunctionResult *result) {
  static_cast<IntegrationTest *>(instance)->onChannelFunctionSetResult(result);
}

void integration_test_on_channel_caption_set_result(
    void *_suplaclient, void *instance, TSCD_SetCaptionResult *result) {
  static_cast<IntegrationTest *>(instance)->onChannelCaptionSetResult(result);
}

void integration_test_on_channel_group_caption_set_result(
    void *_suplaclient, void *instance, TSCD_SetCaptionResult *result) {
  static_cast<IntegrationTest *>(instance)->onChannelGroupCaptionSetResult(
      result);
}

void integration_test_on_location_caption_set_result(
    void *_suplaclient, void *instance, TSCD_SetCaptionResult *result) {
  static_cast<IntegrationTest *>(instance)->onLocationCaptionSetResult(result);
}

void integration_test_on_scene_caption_set_result(
    void *_suplaclient, void *instance, TSCD_SetCaptionResult *result) {
  static_cast<IntegrationTest *>(instance)->onSceneCaptionSetResult(result);
}

void integration_test_on_channel_basic_cfg(void *_suplaclient, void *instance,
                                           TSC_ChannelBasicCfg *cfg) {
  static_cast<IntegrationTest *>(instance)->onChannelBasicCfg(cfg);
}

void integration_test_channel_update(void *_suplaclient, void *instance,
                                     TSC_SuplaChannel_E *channel) {
  static_cast<IntegrationTest *>(instance)->channelUpdate(channel);
}

void integration_test_channel_group_update(
    void *_suplaclient, void *instance,
    TSC_SuplaChannelGroup_B *channel_group) {
  static_cast<IntegrationTest *>(instance)->channelGroupUpdate(channel_group);
}

void integration_test_location_update(void *_suplaclient, void *instance,
                                      TSC_SuplaLocation *location) {
  static_cast<IntegrationTest *>(instance)->locationUpdate(location);
}

void integration_test_scene_update(void *_suplaclient, void *instance,
                                   TSC_SuplaScene *scene) {
  static_cast<IntegrationTest *>(instance)->sceneUpdate(scene);
}

void integration_test_on_registration_enabled(
    void *_suplaclient, void *instance, TSDC_RegistrationEnabled *reg_enabled) {
  static_cast<IntegrationTest *>(instance)->onRegistrationEnabled(reg_enabled);
}

void integration_test_on_set_registration_enabled_result(
    void *_suplaclient, void *instance,
    TSC_SetRegistrationEnabledResult *result) {
  static_cast<IntegrationTest *>(instance)->onSetRegistrationEnabledResult(
      result);
}

void integration_test_on_oauth_token_request_result(
    void *_suplaclient, void *instance, TSC_OAuthTokenRequestResult *result) {
  static_cast<IntegrationTest *>(instance)->onOAuthTokenRequestResult(result);
}

void integration_test_on_action_execution_result(
    void *_suplaclient, void *instance, TSC_ActionExecutionResult *result) {
  static_cast<IntegrationTest *>(instance)->onActionExecutionResult(result);
}

// static
void IntegrationTest::Init(int argc, char **argv) {
  const char kHelpMessage[] =
      "\n"
      "Arguments:\n"
      "   -h         Print this help\n"
      "   --dbname    Database name\n (default: supla_test)\n"
      "   --dbhost    Database server hostname\n (default: db)\n"
      "   --dbuser    Database server username\n (default: supla)\n"
      "   --sqldir    Specifies the path of the sql script directory\n\n";

  for (int a = 1; a < argc; a++) {
    if (strcmp("--sqldir", argv[a]) == 0 && a < argc - 1 &&
        strlen(argv[a + 1]) > 0) {
      IntegrationTest::sqlDir = argv[a + 1];

    } else if (strcmp("--dbname", argv[a]) == 0 && a < argc - 1 &&
               strlen(argv[a + 1]) > 0) {
      IntegrationTest::dbName = argv[a + 1];

    } else if (strcmp("--dbuser", argv[a]) == 0 && a < argc - 1 &&
               strlen(argv[a + 1]) > 0) {
      IntegrationTest::dbUser = argv[a + 1];

    } else if (strcmp("--dbhost", argv[a]) == 0 && a < argc - 1 &&
               strlen(argv[a + 1]) > 0) {
      IntegrationTest::dbHost = argv[a + 1];

    } else if (strcmp("-h", argv[a]) == 0 || strcmp("--help", argv[a]) == 0) {
      printf("%s", kHelpMessage);
    }
  }
}

IntegrationTest::IntegrationTest() {
  iterationCancelled = false;
  sclient = NULL;
}

IntegrationTest::~IntegrationTest() { clientFree(); }

void IntegrationTest::clientInit() {
  if (sclient != NULL) {
    return;
  }

  TSuplaClientCfg scc;
  supla_client_cfginit(&scc);

  scc.protocol_version = SUPLA_PROTO_VERSION;

  snprintf(scc.Name, SUPLA_CLIENT_NAME_MAXSIZE, "Console Test Client");
  snprintf(scc.SoftVer, SUPLA_SOFTVER_MAXSIZE, "1.0-Linux");
  snprintf(scc.Email, SUPLA_EMAIL_MAXSIZE, "test@supla.org");

  fillArrayWithOrdinalNumbers(scc.clientGUID, SUPLA_GUID_SIZE, 0);
  fillArrayWithOrdinalNumbers(scc.AuthKey, SUPLA_AUTHKEY_SIZE, 0);

  char host[] = "127.0.0.1";
  scc.user_data = this;
  scc.host = host;
  scc.tcp_port = 2015;
  scc.ssl_port = 2016;
  scc.ssl_enabled = true;

  scc.cb_on_getversion_result = &integration_test_on_getversion_result;
  scc.cb_on_connected = &integration_test_on_connected;
  scc.cb_on_connerror = &integration_test_on_connerror;
  scc.cb_on_registered = &integration_test_on_registered;
  scc.cb_on_registererror = &integration_test_on_registererror;
  scc.cb_on_superuser_authorization_result =
      &integration_test_on_superuser_authorization_result;
  scc.cb_on_channel_function_set_result =
      &integration_test_on_channel_function_set_result;
  scc.cb_on_channel_caption_set_result =
      &integration_test_on_channel_caption_set_result;
  scc.cb_on_channel_group_caption_set_result =
      &integration_test_on_channel_group_caption_set_result;
  scc.cb_on_location_caption_set_result =
      &integration_test_on_location_caption_set_result;
  scc.cb_on_scene_caption_set_result =
      &integration_test_on_scene_caption_set_result;
  scc.cb_on_channel_basic_cfg = &integration_test_on_channel_basic_cfg;
  scc.cb_channel_update = &integration_test_channel_update;
  scc.cb_channelgroup_update = &integration_test_channel_group_update;
  scc.cb_location_update = &integration_test_location_update;
  scc.cb_scene_update = &integration_test_scene_update;
  scc.cb_on_registration_enabled = &integration_test_on_registration_enabled;
  scc.cb_on_set_registration_enabled_result =
      &integration_test_on_set_registration_enabled_result;
  scc.cb_on_oauth_token_request_result =
      &integration_test_on_oauth_token_request_result;
  scc.cb_on_action_execution_result =
      &integration_test_on_action_execution_result;

  beforeClientInit(&scc);
  sclient = supla_client_init(&scc);
}

void IntegrationTest::fillArrayWithOrdinalNumbers(char *arr, int arr_size,
                                                  char start) {
  for (int a = 0; a < arr_size; a++) {
    arr[a] = start + a;
  }
}

void IntegrationTest::clientFree() {
  if (sclient != NULL) {
    supla_client_free(sclient);
    sclient = NULL;
  }
}

void IntegrationTest::iterateUntilTimeout(bool doRegister,
                                          unsigned int timeoutMS) {
  ASSERT_GT(timeoutMS, (unsigned int)0);
  iterationCancelled = false;

  struct timeval now;
  gettimeofday(&now, NULL);
  unsigned int start_ms = now.tv_sec * 1000 + now.tv_usec / 1000;

  if (sclient == NULL || 0 == supla_client_connected(sclient)) {
    clientFree();
    clientInit();
    if (0 == supla_client_connect(sclient)) {
      clientFree();
      return;
    }
  }

  while (!iterationCancelled) {
    supla_client__iterate(sclient, doRegister ? 1 : 0, 10);

    gettimeofday(&now, NULL);
    unsigned int time_diff = now.tv_sec * 1000 + now.tv_usec / 1000 - start_ms;
    ASSERT_LT(time_diff, timeoutMS);

    usleep(1000);
  }
}

void IntegrationTest::iterateUntilTimeout(unsigned int timeoutMS) {
  iterateUntilTimeout(true, timeoutMS);
}

void IntegrationTest::reconnect() {
  if (sclient != NULL) {
    supla_client_disconnect(sclient);
    clientFree();
  }

  iterateUntilDefaultTimeout();
}

void IntegrationTest::iterateUntilDefaultTimeout() {
  iterateUntilTimeout(5000);
}

void IntegrationTest::runSqlScript(const char *script) {
  MySqlShell::runSqlScript(IntegrationTest::sqlDir, IntegrationTest::dbHost,
                           IntegrationTest::dbUser, IntegrationTest::dbName,
                           script);
}

string IntegrationTest::sqlQuery(const char *query) {
  string result;
  MySqlShell::sqlQuery(IntegrationTest::sqlDir, IntegrationTest::dbHost,
                       IntegrationTest::dbUser, IntegrationTest::dbName, query,
                       &result);

  return result;
}

void IntegrationTest::initTestDatabase() {
  MySqlShell::initTestDatabase(IntegrationTest::sqlDir, IntegrationTest::dbHost,
                               IntegrationTest::dbUser,
                               IntegrationTest::dbName);
}

void IntegrationTest::cancelIteration(void) { iterationCancelled = true; }

void IntegrationTest::beforeClientInit(TSuplaClientCfg *scc) {}

void IntegrationTest::onConnected() {}

void IntegrationTest::onDisconnected() {}

void IntegrationTest::onConnectionError(int code) { ASSERT_TRUE(false); }

void IntegrationTest::onRegistered(TSC_SuplaRegisterClientResult_D *result) {
  ASSERT_FALSE(result == NULL);
  ASSERT_EQ(result->result_code, SUPLA_RESULTCODE_TRUE);
}

void IntegrationTest::onRegistrationError(int code) {}

void IntegrationTest::onSuperuserAuthorizationResult(bool authorized,
                                                     int code) {}

void IntegrationTest::onChannelFunctionSetResult(
    TSC_SetChannelFunctionResult *result) {}

void IntegrationTest::onChannelCaptionSetResult(TSCD_SetCaptionResult *result) {
}

void IntegrationTest::onChannelGroupCaptionSetResult(
    TSCD_SetCaptionResult *result) {}

void IntegrationTest::onLocationCaptionSetResult(
    TSCD_SetCaptionResult *result) {}

void IntegrationTest::onSceneCaptionSetResult(TSCD_SetCaptionResult *result) {}

void IntegrationTest::onChannelBasicCfg(TSC_ChannelBasicCfg *cfg) {}

void IntegrationTest::channelUpdate(TSC_SuplaChannel_E *channel) {}

void IntegrationTest::channelGroupUpdate(
    TSC_SuplaChannelGroup_B *channel_group) {}

void IntegrationTest::locationUpdate(TSC_SuplaLocation *location) {}

void IntegrationTest::sceneUpdate(TSC_SuplaScene *scene) {}

void IntegrationTest::onRegistrationEnabled(
    TSDC_RegistrationEnabled *reg_enabled) {}

void IntegrationTest::onSetRegistrationEnabledResult(
    TSC_SetRegistrationEnabledResult *result) {}

void IntegrationTest::onGetVersionResult(TSDC_SuplaGetVersionResult *result) {}

void IntegrationTest::onOAuthTokenRequestResult(
    TSC_OAuthTokenRequestResult *result) {}

void IntegrationTest::onActionExecutionResult(
    TSC_ActionExecutionResult *result) {}

} /* namespace testing */
