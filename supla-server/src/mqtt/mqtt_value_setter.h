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

#ifndef MQTT_CHANNEl_VALUE_SETTER_H_
#define MQTT_CHANNEl_VALUE_SETTER_H_

#include "actions/action_executor.h"
#include "mqtt_abstract_value_setter.h"
#include "user.h"

class supla_mqtt_value_setter : public supla_mqtt_abstract_value_setter {
 private:
  supla_action_executor *action_executor;

 protected:
  supla_action_executor *get_action_executor(void);
  virtual void set_on(bool on);
  virtual void set_color(unsigned int color);
  virtual void set_brightness(char brightness);
  virtual void set_color_brightness(char brightness);
  virtual void action_toggle(void);
  virtual void action_shut(
      const supla_action_shading_system_parameters *params);
  virtual void action_reveal(void);
  virtual void action_up(void);
  virtual void action_down(void);
  virtual void action_up_or_stop(void);
  virtual void action_down_or_stop(void);
  virtual void action_step_by_step(void);
  virtual void action_stop(void);
  virtual void action_open(void);
  virtual void action_close(void);
  virtual void action_open_close(void);
  virtual void action_hvac_set_parameters(supla_action_hvac_parameters *params);
  virtual void action_hvac_set_temperature(
      supla_action_hvac_setpoint_temperature *temperature);
  virtual void action_hvac_set_temperatures(
      supla_action_hvac_setpoint_temperatures *temperatures);
  virtual void refresh_all_existing(void);

 public:
  explicit supla_mqtt_value_setter(supla_mqtt_client_settings *settings);
  virtual ~supla_mqtt_value_setter(void);
};

#endif /*MQTT_CHANNEl_VALUE_SETTER_H_*/
