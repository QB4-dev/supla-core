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

#ifndef PUSH_NOTIFICATION_RECIPIENTS_H_
#define PUSH_NOTIFICATION_RECIPIENTS_H_

#include <map>
#include <vector>

#include "http/remote_gateway_access_token.h"
#include "json/cJSON.h"
#include "push/pn_recipient.h"

class supla_pn_recipients {
 private:
  std::map<_platform_e, std::vector<supla_pn_recipient*>> recipients;
  bool get_ids(cJSON* json, std::vector<int>* ids);

 public:
  supla_pn_recipients(void);
  virtual ~supla_pn_recipients(void);
  supla_pn_recipient* get(_platform_e platform, size_t index);
  supla_pn_recipient* get(size_t index);
  size_t count(_platform_e platform);
  size_t total_count(void);
  void add(supla_pn_recipient* recipient, _platform_e platform);
  void clear(void);
  bool apply_json(int user_id, cJSON* json);

  supla_pn_recipients& operator=(const supla_pn_recipients& src);
};

#endif /* PUSH_NOTIFICATION_RECIPIENTS_H_ */
