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

#ifndef ACTION_COMMMAND_MOCK_H_
#define ACTION_COMMMAND_MOCK_H_

#include <gmock/gmock.h>

#include "ipc/abstract_action_command.h"

namespace testing {

class ActionCommandMock : public supla_abstract_action_command {
 public:
  explicit ActionCommandMock(supla_abstract_ipc_socket_adapter *socket_adapter,
                             int action);
  MOCK_METHOD6(action_open_close,
               bool(int user_id, int device_id, int channel_id, bool open,
                    const char *alexa_correlation_token,
                    const char *google_request_id));
  MOCK_METHOD3(action_turn_on,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_turn_off,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_toggle, bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_stop, bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_up_or_stop,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_down_or_stop,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_step_by_step,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD5(action_copy, bool(int user_id, int device_id, int channel_id,
                                 int source_device_id, int source_channel_id));
  MOCK_METHOD4(action_shut,
               bool(int user_id, int device_id, int channel_id,
                    const supla_action_shading_system_parameters *params));
  MOCK_METHOD4(action_hvac_set_parameters,
               bool(int user_id, int device_id, int channel_id,
                    const supla_action_hvac_parameters *params));
  MOCK_METHOD3(action_hvac_switch_to_manual_mode,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD3(action_hvac_switch_to_program_mode,
               bool(int user_id, int device_id, int channel_id));
  MOCK_METHOD4(action_hvac_set_temperature,
               bool(int user_id, int device_id, int channel_id,
                    const supla_action_hvac_setpoint_temperature *temperature));
  MOCK_METHOD4(
      action_hvac_set_temperatures,
      bool(int user_id, int device_id, int channel_id,
           const supla_action_hvac_setpoint_temperatures *temperatures));
};

} /* namespace testing */

#endif /* ACTION_COMMMAND_MOCK_H_ */
