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

#include "abstract_get_gpm_value_command.h"

#include <string.h>

#include "ipc/abstract_ipc_ctrl.h"
#include "math.h"
#include "tools.h"

using std::string;

supla_abstract_get_gpm_value_command::supla_abstract_get_gpm_value_command(
    supla_abstract_ipc_socket_adapter *socket_adapter)
    : supla_abstract_ipc_command(socket_adapter) {}

const string supla_abstract_get_gpm_value_command::get_command_name(void) {
  return "GET-GPM-VALUE:";
}

void supla_abstract_get_gpm_value_command::on_command_match(
    const char *params) {
  process_parameters(
      params, [this](int user_id, int device_id, int channel_id) -> bool {
        double value = NAN;
        if (!get_gpm_value(user_id, device_id, channel_id, &value)) {
          return false;
        }

        char buffer[50] = {};
        snprintf(buffer, sizeof(buffer), "VALUE:%f", value);

        send_result(buffer);
        return true;
      });
}
