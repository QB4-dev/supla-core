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

#ifndef ELECTRICITYMETERCONFIG_H_
#define ELECTRICITYMETERCONFIG_H_

#include <map>
#include <string>

#include "jsonconfig/json_config.h"
#include "proto.h"

class supla_channel_em_extended_value;
class electricity_meter_config : public supla_json_config {
 private:
  static const char counters_available_key[];
  static const char em_initial_values_key[];
  static const char add_to_history_key[];
  static const char upper_voltage_threshold_key[];
  static const char lower_voltage_threshold_key[];
  static const char disabled_phases_key[];
  static const char voltage_logger_enabled_key[];
  static const char current_logger_enabled_key[];
  static const char power_active_logger_enabled_key[];
  static const std::map<int, std::string> var_map;

 protected:
  int get_available_counters(void);
  void add_initial_value(_supla_int64_t initial_value,
                         bool initial_value_for_all_phases, unsigned char phase,
                         int flags, unsigned _supla_int64_t *value,
                         _supla_int64_t *substracted);
  void add_initial_value(int var, int flags, unsigned _supla_int64_t value[]);

 public:
  explicit electricity_meter_config(supla_json_config *root);
  electricity_meter_config(void);
  bool should_be_added_to_history(void);
  double get_upper_voltage_threshold(void);
  double get_lower_voltage_threshold(void);
  bool is_phase_disabled(unsigned char phase);
  int get_channel_user_flags(void);
  bool update_available_counters(int measured_values);
  bool update_available_counters(supla_channel_em_extended_value *em);
  _supla_int64_t get_initial_value(int var, unsigned char phase,
                                   bool *initial_value_for_all_phases);
  _supla_int64_t get_initial_value_for_all_phases(int var);
  void add_initial_value(int var, unsigned char phase, int flags,
                         unsigned _supla_int64_t *value);
  void add_initial_value(int var, unsigned _supla_int64_t *value);

  void add_initial_values(int flags, TElectricityMeter_ExtendedValue_V2 *em_ev);
  void add_initial_value(unsigned _supla_int_t *total_forward_active_energy);

  bool is_voltage_logger_enabled(void);
  bool is_current_logger_enabled(void);
  bool is_power_active_logger_enabled(void);
};

#endif /* ELECTRICITYMETERCONFIG_H_ */
