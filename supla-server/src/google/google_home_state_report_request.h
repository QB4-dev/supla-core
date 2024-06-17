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

#ifndef GOOGLE_HOME_STATE_REPORT_REQUEST_H_
#define GOOGLE_HOME_STATE_REPORT_REQUEST_H_

#include <string>

#include "google/google_home_credentials.h"
#include "http/asynctask_http_request.h"
#include "http/remote_gateway_access_token_provider.h"

class supla_google_home_state_report_request
    : public supla_asynctask_http_request {
 private:
  supla_google_home_credentials *credentials;
  supla_remote_gateway_access_token_provider *token_provider;
  std::string request_id;

 protected:
  virtual bool make_request(supla_abstract_curl_adapter *curl_adapter);
  virtual std::string get_name(void);
  std::string get_request_id(void);
  void set_request_id(const std::string &request_id);

 public:
  supla_google_home_state_report_request(
      const supla_caller &caller, int user_id, int device_id, int channel_id,
      supla_asynctask_queue *queue, supla_abstract_asynctask_thread_pool *pool,
      supla_abstract_channel_property_getter *property_getter,
      supla_google_home_credentials *credentials,
      supla_remote_gateway_access_token_provider *token_provider,
      const std::string &request_id);

  static bool is_caller_allowed(const supla_caller &caller);
  static bool is_function_allowed(int func);

  static void new_request(const supla_caller &caller, supla_user *user,
                          int device_id, int channel_id,
                          const std::string &request_id);
};

#endif /* GOOGLE_HOME_STATE_REPORT_REQUEST_H_ */
