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

#include "pn_recipient_dao.h"

#include <string>

#include "log.h"
#include "proto.h"

using std::string;

supla_pn_recipient_dao::supla_pn_recipient_dao(
    supla_abstract_db_access_provider *dba) {
  this->dba = dba;
}

supla_pn_recipient_dao::~supla_pn_recipient_dao(void) {}

void supla_pn_recipient_dao::remove(int user_id,
                                    supla_pn_recipient *recipient) {
  if (!user_id || !recipient || !recipient->get_client_id()) {
    return;
  }

  bool already_connected = dba->is_connected();

  if (!already_connected && !dba->connect()) {
    return;
  }

  MYSQL_BIND pbind[2] = {};

  int client_id = recipient->get_client_id();

  pbind[0].buffer_type = MYSQL_TYPE_LONG;
  pbind[0].buffer = (char *)&user_id;

  pbind[1].buffer_type = MYSQL_TYPE_LONG;
  pbind[1].buffer = (char *)&client_id;

  const char sql[] = "CALL `supla_remove_push_recipients`(?,?)";

  MYSQL_STMT *stmt = nullptr;
  dba->stmt_execute((void **)&stmt, sql, &pbind, 2, true);

  if (stmt != nullptr) {
    mysql_stmt_close(stmt);
  }

  if (!already_connected) {
    dba->disconnect();
  }
}

void supla_pn_recipient_dao::get_recipients(const char *sql, MYSQL_BIND *pbind,
                                            int pbind_size,
                                            supla_pn_recipients *recipients) {
  recipients->clear();

  bool already_connected = dba->is_connected();

  if (!already_connected && !dba->connect()) {
    return;
  }

  MYSQL_STMT *stmt = NULL;

  if (dba->stmt_execute((void **)&stmt, sql, pbind, pbind_size, true)) {
    MYSQL_BIND rbind[7] = {};

    char token[SUPLA_PN_CLIENT_TOKEN_MAXSIZE] = {};
    char profile_name[SUPLA_PN_PROFILE_NAME_MAXSIZE] = {};
    int client_id = 0;
    char platform = 0;
    int app_id = 0;
    char devel_env = 0;
    int protocol_version = 0;

    unsigned long token_len = 0;
    my_bool token_is_null = false;

    unsigned long profile_name_len = 0;
    my_bool profile_name_is_null = false;

    rbind[0].buffer_type = MYSQL_TYPE_STRING;
    rbind[0].buffer = token;
    rbind[0].buffer_length = sizeof(token);
    rbind[0].length = &token_len;
    rbind[0].is_null = &token_is_null;

    rbind[1].buffer_type = MYSQL_TYPE_LONG;
    rbind[1].buffer = (char *)&client_id;
    rbind[1].buffer_length = sizeof(client_id);

    rbind[2].buffer_type = MYSQL_TYPE_TINY;
    rbind[2].buffer = &platform;
    rbind[2].buffer_length = sizeof(platform);

    rbind[3].buffer_type = MYSQL_TYPE_LONG;
    rbind[3].buffer = (char *)&app_id;
    rbind[3].buffer_length = sizeof(app_id);

    rbind[4].buffer_type = MYSQL_TYPE_TINY;
    rbind[4].buffer = &devel_env;
    rbind[4].buffer_length = sizeof(devel_env);

    rbind[5].buffer_type = MYSQL_TYPE_STRING;
    rbind[5].buffer = profile_name;
    rbind[5].buffer_length = sizeof(profile_name);
    rbind[5].length = &profile_name_len;
    rbind[5].is_null = &profile_name_is_null;

    rbind[6].buffer_type = MYSQL_TYPE_LONG;
    rbind[6].buffer = &protocol_version;
    rbind[6].buffer_length = sizeof(protocol_version);

    if (mysql_stmt_bind_result(stmt, rbind)) {
      supla_log(LOG_ERR, "MySQL - stmt bind error - %s",
                mysql_stmt_error(stmt));
    } else {
      mysql_stmt_store_result(stmt);

      if (mysql_stmt_num_rows(stmt) > 0) {
        while (!mysql_stmt_fetch(stmt)) {
          dba->set_terminating_byte(token, sizeof(token), token_len,
                                    token_is_null);
          dba->set_terminating_byte(profile_name, sizeof(profile_name),
                                    profile_name_len, profile_name_is_null);
          supla_pn_recipient *recipient =
              new supla_pn_recipient(client_id, app_id, devel_env > 0, token,
                                     profile_name, protocol_version);
          if (recipient) {
            recipients->add(recipient, static_cast<_platform_e>(platform));
          }
        }
      }
    }

    mysql_stmt_close(stmt);
  }

  if (!already_connected) {
    dba->disconnect();
  }
}

void supla_pn_recipient_dao::get_recipients(int user_id,
                                            int push_notification_id,
                                            supla_pn_recipients *recipients) {
  const char sql[] =
      "SELECT c.push_token, c.id, c.platform, c.app_id, c.devel_env, "
      "c.profile_name, c.protocol_version FROM supla_client c, "
      "supla_rel_aid_pushnotification p, supla_v_accessid_active a WHERE "
      "p.push_notification_id = ? AND c.user_id = ? AND c.access_id = "
      "p.access_id AND c.push_token IS NOT NULL AND c.access_id = a.id AND "
      "c.enabled = 1 AND a.enabled = 1 AND a.is_now_active = 1 AND "
      "TIMESTAMPDIFF(MONTH, c.push_token_update_time, UTC_TIMESTAMP()) < 2 AND "
      "(c.platform = 1 OR c.platform = 2)";

  MYSQL_BIND pbind[2] = {};

  pbind[0].buffer_type = MYSQL_TYPE_LONG;
  pbind[0].buffer = (char *)&push_notification_id;

  pbind[1].buffer_type = MYSQL_TYPE_LONG;
  pbind[1].buffer = (char *)&user_id;

  get_recipients(sql, pbind, 2, recipients);
}

void supla_pn_recipient_dao::get_recipients(int user_id,
                                            const std::vector<int> &aids,
                                            const std::vector<int> &cids,
                                            supla_pn_recipients *recipients) {
  if (aids.size() == 0 && cids.size() == 0) {
    recipients->clear();
    return;
  }

  string sql =
      "SELECT c.push_token, c.id, c.platform, c.app_id, c.devel_env, "
      "c.profile_name, c.protocol_version FROM supla_client c, "
      "supla_v_accessid_active a WHERE c.user_id = ? AND c.push_token IS NOT "
      "NULL AND c.access_id = a.id AND c.enabled = 1 AND a.enabled = 1 AND "
      "a.is_now_active = 1 AND (c.platform = 1 OR c.platform = 2) AND "
      "TIMESTAMPDIFF(MONTH, c.push_token_update_time, UTC_TIMESTAMP()) < 2 AND "
      "((c.access_id != 0 AND c.access_id IN (0";

  for (size_t a = 0; a < aids.size(); a++) {
    sql.append(",?");
  }

  sql.append(")) OR c.id IN (0");

  for (size_t a = 0; a < cids.size(); a++) {
    sql.append(",?");
  }

  sql.append("))");

  int bind_size = 1 + aids.size() + cids.size();

  MYSQL_BIND *pbind = new MYSQL_BIND[bind_size]();
  if (!pbind) {
    return;
  }

  int *ids = new int[aids.size() + cids.size()]();
  if (!ids) {
    delete[] pbind;
    return;
  }

  pbind[0].buffer_type = MYSQL_TYPE_LONG;
  pbind[0].buffer = (char *)&user_id;

  int n = 1;
  for (auto it = aids.begin(); it != aids.end(); ++it) {
    ids[n - 1] = *it;
    pbind[n].buffer_type = MYSQL_TYPE_LONG;
    pbind[n].buffer = (char *)&ids[n - 1];
    n++;
  }

  for (auto it = cids.begin(); it != cids.end(); ++it) {
    ids[n - 1] = *it;
    pbind[n].buffer_type = MYSQL_TYPE_LONG;
    pbind[n].buffer = (char *)&ids[n - 1];
    n++;
  }

  get_recipients(sql.c_str(), pbind, bind_size, recipients);

  delete[] pbind;
  delete[] ids;
}
