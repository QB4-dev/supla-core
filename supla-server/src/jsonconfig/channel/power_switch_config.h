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

#ifndef POWER_SWITCH_CONFIG_H_
#define POWER_SWITCH_CONFIG_H_

#include <map>
#include <string>

#include "device/abstract_common_channel_properties.h"
#include "jsonconfig/json_config.h"

class power_switch_config : public supla_json_config {
 private:
  static const std::map<unsigned _supla_int16_t, std::string> field_map;
  static const char related_meter_channel_id_field[];

 public:
  explicit power_switch_config(supla_json_config *root);
  power_switch_config(void);
  virtual ~power_switch_config(void);
  void set_config(TChannelConfig_PowerSwitch *config,
                  supla_abstract_common_channel_properties *props);
  bool get_config(TChannelConfig_PowerSwitch *config);
  virtual void merge(supla_json_config *dst);
  int get_related_meter_channel_id(void);
};

#endif /* POWER_SWITCH_CONFIG_H_ */
