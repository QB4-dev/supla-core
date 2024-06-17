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

#ifndef ABSTRACT_PUSH_NOTIFICATION_GATEWAY_CLIENT_H_
#define ABSTRACT_PUSH_NOTIFICATION_GATEWAY_CLIENT_H_

#include <string>
#include <vector>

#include "caller.h"
#include "http/abstract_curl_adapter.h"
#include "http/remote_gateway_access_token_provider.h"
#include "json/cJSON.h"
#include "push/push_notification.h"

class supla_abstract_pn_gateway_client {
 private:
  supla_caller caller;
  supla_remote_gateway_access_token_provider *token_provider;
  supla_push_notification *push;
  supla_abstract_curl_adapter *curl_adapter;

 protected:
  supla_push_notification *get_push_notification(void);
  supla_abstract_curl_adapter *get_curl_adapter(void);
  void add_args(const std::vector<std::string> &args,
                const std::string &key_name, cJSON *parent,
                bool use_strings_instead_of_array);

  virtual _platform_e get_platform(void) = 0;
  virtual bool _send(supla_remote_gateway_access_token *token,
                     supla_pn_recipient *recipient) = 0;
  const supla_caller &get_caller(void);

 public:
  supla_abstract_pn_gateway_client(
      const supla_caller &caller, supla_abstract_curl_adapter *curl_adapter,
      supla_remote_gateway_access_token_provider *token_provider,
      supla_push_notification *push);
  virtual ~supla_abstract_pn_gateway_client(void);
  bool send(void);
};

#endif /* ABSTRACT_PUSH_NOTIFICATION_GATEWAY_CLIENT_H_ */
