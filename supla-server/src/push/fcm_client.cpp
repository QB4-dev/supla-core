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

#include "fcm_client.h"

#include <regex>  // NOLINT

#include "json/cJSON.h"
#include "log.h"
#include "svrcfg.h"

using std::regex;
using std::smatch;
using std::string;

supla_fcm_client::supla_fcm_client(
    const supla_caller &caller, supla_abstract_curl_adapter *curl_adapter,
    supla_remote_gateway_access_token_provider *token_provider,
    supla_push_notification *push)
    : supla_abstract_pn_gateway_client(caller, curl_adapter, token_provider,
                                       push) {}

supla_fcm_client::~supla_fcm_client(void) {}

_platform_e supla_fcm_client::get_platform(void) {
  return platform_push_android;
}

char *supla_fcm_client::get_payload(supla_pn_recipient *recipient) {
  cJSON *root = cJSON_CreateObject();
  cJSON *message = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "message", message);

  cJSON_AddStringToObject(message, "token", recipient->get_token().c_str());
  cJSON *android = cJSON_CreateObject();
  cJSON_AddItemToObject(message, "android", android);
  cJSON_AddStringToObject(android, "priority", "high");

  cJSON *data = cJSON_CreateObject();
  if (!recipient->get_profile_name().empty()) {
    cJSON_AddStringToObject(data, "profileName",
                            recipient->get_profile_name().c_str());
  }

  if (get_caller().get_id()) {
    string id = std::to_string(get_caller().get_id());

    if (get_caller() == ctDevice) {
      cJSON_AddStringToObject(data, "deviceId", id.c_str());
    } else if (get_caller() == ctChannel) {
      cJSON_AddStringToObject(data, "channelId", id.c_str());
    }
  }

  cJSON *notification = nullptr;

  bool ge23 = recipient->get_protocol_version() >= 23;

  if (ge23) {
    notification = data;
  } else {
    notification = cJSON_CreateObject();
    cJSON_AddItemToObject(android, "notification", notification);
  }

  if (!get_push_notification()->get_title().empty()) {
    cJSON_AddStringToObject(notification, "title",
                            get_push_notification()->get_title().c_str());
  }

  if (!get_push_notification()->get_body().empty()) {
    cJSON_AddStringToObject(notification, "body",
                            get_push_notification()->get_body().c_str());
  }

  if (!get_push_notification()->get_localized_title().empty()) {
    cJSON_AddStringToObject(
        notification, "title_loc_key",
        get_push_notification()->get_localized_title().c_str());
  }

  if (get_push_notification()->get_localized_title_args().size()) {
    add_args(get_push_notification()->get_localized_title_args(),
             ge23 ? "title_loc_arg" : "title_loc_args", notification, ge23);
  }

  if (!get_push_notification()->get_localized_body().empty()) {
    cJSON_AddStringToObject(
        notification, "body_loc_key",
        get_push_notification()->get_localized_body().c_str());
  }

  if (get_push_notification()->get_localized_body_args().size()) {
    add_args(get_push_notification()->get_localized_body_args(),
             ge23 ? "body_loc_arg" : "body_loc_args", notification, ge23);
  }

  if (cJSON_GetArraySize(data)) {
    cJSON_AddItemToObject(android, "data", data);
  } else {
    cJSON_Delete(data);
  }

  char *payload = cJSON_PrintUnformatted(root);
  cJSON_Delete(root);

  return payload;
}

string supla_fcm_client::get_message_id(const string &request_result) {
  string result;

  cJSON *root = cJSON_Parse(request_result.c_str());
  if (!root) {
    return result;
  }

  cJSON *name = cJSON_GetObjectItem(root, "name");
  if (name && cJSON_IsString(name)) {
    string value = cJSON_GetStringValue(name);
    regex pattern("projects/.*/messages/(.*)");
    smatch matches;
    if (std::regex_search(value, matches, pattern)) {
      result = matches[1];
    }
  }

  cJSON_Delete(root);

  return result;
}

bool supla_fcm_client::_send(supla_remote_gateway_access_token *token,
                             supla_pn_recipient *recipient) {
  get_curl_adapter()->append_header("Content-Type: application/json");
  string _token = "Authorization: Bearer " + token->get_token();
  get_curl_adapter()->append_header(_token.c_str());

  get_curl_adapter()->set_opt_url(
      token->get_url(recipient->is_development_env()).c_str());
  char *payload = get_payload(recipient);
  get_curl_adapter()->set_opt_post_fields(payload);

  string request_result;
  get_curl_adapter()->set_opt_write_data(&request_result);

  bool result = get_curl_adapter()->perform();
  free(payload);

  if (result) {
    result = get_curl_adapter()->get_response_code() == 200;
    if (!result) {
      if (get_curl_adapter()->get_response_code() == 404 ||
          get_curl_adapter()->get_response_code() == 403) {
        recipient->set_exists(false);
      } else {
        supla_log(LOG_ERR, "The FCM server returned an unexpected code: %i",
                  get_curl_adapter()->get_response_code());
      }

    } else {
      string message_id = get_message_id(request_result);
      if (message_id.empty()) {
        supla_log(LOG_ERR,
                  "The FCM server response does not contain the message ID.");
      } else {
        recipient->set_message_id(message_id);
      }
    }
  }

  return result;
}
