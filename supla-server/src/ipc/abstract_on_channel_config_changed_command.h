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

#ifndef SUPLA_ABSTRACT_ON_CHANNEL_CONFIG_CHANGED_COMMAND_H_
#define SUPLA_ABSTRACT_ON_CHANNEL_CONFIG_CHANGED_COMMAND_H_

#include <string>

#include "ipc/abstract_ipc_command.h"

#define CONFIG_CHANGE_SCOPE_FUNCTION 0x1
#define CONFIG_CHANGE_SCOPE_CAPTION 0x2
#define CONFIG_CHANGE_SCOPE_LOCATION 0x4
#define CONFIG_CHANGE_SCOPE_VISIBILITY 0x8
#define CONFIG_CHANGE_SCOPE_ICON 0x10
#define CONFIG_CHANGE_SCOPE_JSON_DEFAULT 0x20
#define CONFIG_CHANGE_SCOPE_JSON_WEEKLY_SCHEDULE 0x40
#define CONFIG_CHANGE_SCOPE_JSON_ALT_WEEKLY_SCHEDULE 0x80
#define CONFIG_CHANGE_SCOPE_RELATIONS 0x100
#define CONFIG_CHANGE_SCOPE_ALEXA_INTEGRATION_ENABLED 0x200

class supla_abstract_on_channel_config_changed_command
    : public supla_abstract_ipc_command {
 protected:
  virtual void on_command_match(const char *params);
  virtual const std::string get_command_name(void);
  virtual void on_channel_config_changed(int user_id, int device_id,
                                         int channel_id, int type, int func,
                                         unsigned long long scope) = 0;

 public:
  explicit supla_abstract_on_channel_config_changed_command(
      supla_abstract_ipc_socket_adapter *socket_adapter);
};

#endif /* SUPLA_ABSTRACT_ON_CHANNEL_CONFIG_CHANGED_COMMAND_H_ */
