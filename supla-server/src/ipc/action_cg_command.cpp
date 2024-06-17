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

#include "ipc/action_cg_command.h"

#include "actions/action_executor.h"
#include "device/channel_property_getter.h"
#include "user.h"
#include "user/userchannelgroups.h"

supla_action_cg_command::supla_action_cg_command(
    supla_abstract_ipc_socket_adapter *socket_adapter, int action)
    : supla_abstract_action_cg_command(socket_adapter, action) {}

bool supla_action_cg_command::action_open_close(supla_user *user, int group_id,
                                                bool open) {
  bool result = false;
  if (open) {
    result = user->get_channel_groups()->action_open(get_caller(), group_id);
  } else {
    result = user->get_channel_groups()->action_close(get_caller(), group_id);
  }

  return result;
}

bool supla_action_cg_command::action_turn_off(supla_user *user, int group_id) {
  return user->get_channel_groups()->set_on(get_caller(), group_id, false);
}

bool supla_action_cg_command::action_turn_on(supla_user *user, int group_id) {
  return user->get_channel_groups()->set_on(get_caller(), group_id, true);
}

bool supla_action_cg_command::action_toggle(supla_user *user, int group_id) {
  return user->get_channel_groups()->action_toggle(get_caller(), group_id);
}

bool supla_action_cg_command::action_stop(supla_user *user, int group_id) {
  return user->get_channel_groups()->action_stop(get_caller(), group_id);
}

bool supla_action_cg_command::action_up_or_stop(supla_user *user,
                                                int group_id) {
  return user->get_channel_groups()->action_up_or_stop(get_caller(), group_id);
}

bool supla_action_cg_command::action_down_or_stop(supla_user *user,
                                                  int group_id) {
  return user->get_channel_groups()->action_down_or_stop(get_caller(),
                                                         group_id);
}

bool supla_action_cg_command::action_step_by_step(supla_user *user,
                                                  int group_id) {
  return user->get_channel_groups()->action_step_by_step(get_caller(),
                                                         group_id);
}

bool supla_action_cg_command::action_copy(supla_user *user, int group_id,
                                          int source_device_id,
                                          int source_channel_id) {
  bool result = false;

  supla_action_executor *action_executor = new supla_action_executor();
  action_executor->set_caller(get_caller());
  if (action_executor) {
    action_executor->set_group_id(user->getUserID(), group_id);

    supla_channel_property_getter *property_getter =
        new supla_channel_property_getter();
    if (property_getter) {
      action_executor->copy(property_getter, source_device_id,
                            source_channel_id);
      result = true;
      delete property_getter;
      property_getter = NULL;
    }

    delete action_executor;
    action_executor = NULL;
  }
  return result;
}

bool supla_action_cg_command::action_shut(
    supla_user *user, int group_id,
    const supla_action_shading_system_parameters *params) {
  return user->get_channel_groups()->action_shut(get_caller(), group_id,
                                                 params);
}

bool supla_action_cg_command::action_hvac_set_parameters(
    supla_user *user, int group_id,
    const supla_action_hvac_parameters *params) {
  return user->get_channel_groups()->action_hvac_set_parameters(
      get_caller(), group_id, params);
}

bool supla_action_cg_command::action_hvac_switch_to_manual_mode(
    supla_user *user, int group_id) {
  return user->get_channel_groups()->action_hvac_switch_to_manual_mode(
      get_caller(), group_id);
}

bool supla_action_cg_command::action_hvac_switch_to_program_mode(
    supla_user *user, int group_id) {
  return user->get_channel_groups()->action_hvac_switch_to_program_mode(
      get_caller(), group_id);
}

bool supla_action_cg_command::action_hvac_set_temperature(
    supla_user *user, int group_id,
    const supla_action_hvac_setpoint_temperature *temperature) {
  return user->get_channel_groups()->action_hvac_set_temperature(
      get_caller(), group_id, temperature);
}

bool supla_action_cg_command::action_hvac_set_temperatures(
    supla_user *user, int group_id,
    const supla_action_hvac_setpoint_temperatures *temperatures) {
  return user->get_channel_groups()->action_hvac_set_temperatures(
      get_caller(), group_id, temperatures);
}
