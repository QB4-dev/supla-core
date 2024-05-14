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

#include "mqtt_value_setter.h"

#include "actions/action_hvac_setpoint_temperature.h"
#include "actions/action_hvac_setpoint_temperatures.h"
#include "device.h"
#include "mqtt_client_suite.h"
#include "tools.h"

supla_mqtt_value_setter::supla_mqtt_value_setter(
    supla_mqtt_client_settings *settings)
    : supla_mqtt_abstract_value_setter(settings) {
  action_executor = NULL;
}

supla_mqtt_value_setter::~supla_mqtt_value_setter(void) {
  if (action_executor) {
    delete action_executor;
    action_executor = NULL;
  }
}

supla_action_executor *supla_mqtt_value_setter::get_action_executor(void) {
  if (action_executor == NULL) {
    action_executor = new supla_action_executor();
  }

  if (action_executor) {
    action_executor->set_caller(supla_caller(ctMQTT));
    action_executor->set_channel_id(supla_user::find_by_suid(get_suid()),
                                    get_device_id(), get_channel_id());
  }

  return action_executor;
}

void supla_mqtt_value_setter::set_on(bool on) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->set_on(on, 0);
  }
}

void supla_mqtt_value_setter::set_color(unsigned int color) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->set_color(color);
  }
}

void supla_mqtt_value_setter::set_brightness(char brightness) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->set_brightness(brightness);
  }
}

void supla_mqtt_value_setter::set_color_brightness(char brightness) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->set_color_brightness(brightness);
  }
}

void supla_mqtt_value_setter::action_toggle(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->toggle();
  }
}

void supla_mqtt_value_setter::action_shut(
    const supla_action_shading_system_parameters *params) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->shut(params);
  }
}

void supla_mqtt_value_setter::action_reveal(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->reveal();
  }
}

void supla_mqtt_value_setter::action_up(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->up();
  }
}

void supla_mqtt_value_setter::action_down(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->down();
  }
}

void supla_mqtt_value_setter::action_up_or_stop(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->up_or_stop();
  }
}

void supla_mqtt_value_setter::action_down_or_stop(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->down_or_stop();
  }
}

void supla_mqtt_value_setter::action_step_by_step(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->step_by_step();
  }
}

void supla_mqtt_value_setter::action_stop(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->stop();
  }
}

void supla_mqtt_value_setter::action_open(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->open();
  }
}

void supla_mqtt_value_setter::action_close(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->close();
  }
}

void supla_mqtt_value_setter::action_open_close(void) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->open_close();
  }
}

void supla_mqtt_value_setter::action_hvac_set_temperature(
    supla_action_hvac_setpoint_temperature *temperature) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->hvac_set_temperature(temperature);
  }
}

void supla_mqtt_value_setter::action_hvac_set_parameters(
    supla_action_hvac_parameters *params) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->hvac_set_parameters(params);
  }
}

void supla_mqtt_value_setter::action_hvac_set_temperatures(
    supla_action_hvac_setpoint_temperatures *temperatures) {
  supla_action_executor *action = get_action_executor();
  if (action) {
    action->hvac_set_temperatures(temperatures);
  }
}

void supla_mqtt_value_setter::refresh_all_existing(void) {
  int user_id = supla_user::suid_to_user_id(get_suid(), true);
  if (user_id) {
    supla_mqtt_client_suite::globalInstance()->onUserDataChanged(user_id);
  }
}
