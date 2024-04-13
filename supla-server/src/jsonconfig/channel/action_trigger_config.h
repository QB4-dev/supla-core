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

#ifndef ACTIONTRIGGERCONFIG_H_
#define ACTIONTRIGGERCONFIG_H_

#include <functional>
#include <map>
#include <string>

#include "actions/abstract_action_config.h"
#include "jsonconfig/json_config.h"

#define DISABLE_LOCAL_FUNCTION 10200

typedef struct {
  int actionId;
  bool channelGroup;
  int subjectId;

  int sourceDeviceId;
  int sourceChannelId;
} _at_config_action_t;

class action_trigger_config : public abstract_action_config,
                              public supla_json_config {
 private:
  static const std::map<int, std::string> cap_map;
  static const char caps_key[];
  static const char disables_local_operation_key[];
  static const char action_key[];
  static const char actions_key[];
  static const char param_key[];
  int to_cap(cJSON *item);
  const char *to_string(int cap);
  int to_cap(const char *str);
  cJSON *get_cap_user_config(int cap);
  unsigned int get_capabilities(const char *key);
  bool set_capabilities(const char *key, std::function<unsigned int()> get_caps,
                        unsigned int caps);
  supla_abstract_action_parameters *get_parameters(
      std::function<supla_abstract_action_parameters *(cJSON *)> on_json_param);
  int get_action_id(int cap);
  _subjectType_e get_subject_type(int cap);
  int get_subject_id(int cap);
  int get_source_id(const char *key);
  int active_cap;
  int channel_id_if_subject_not_set;
  supla_abstract_action_parameters *get_shading_system(void);
  supla_abstract_action_parameters *get_rgbw(void);
  supla_abstract_action_parameters *get_temperature(void);
  supla_abstract_action_parameters *get_temperatures(void);

 public:
  explicit action_trigger_config(supla_json_config *root);
  action_trigger_config(void);
  virtual ~action_trigger_config(void);

  virtual int get_action_id(void);
  virtual _subjectType_e get_subject_type(void);
  virtual int get_subject_id(void);
  void set_channel_id_if_subject_not_set(int subject_id);

  virtual int get_source_device_id(void);
  virtual int get_source_channel_id(void);

  unsigned int get_capabilities(void);
  bool set_capabilities(unsigned int caps);
  unsigned int get_caps_that_disables_local_operation(void);
  bool set_caps_that_disables_local_operation(unsigned int caps);
  unsigned int get_active_actions(void);
  virtual supla_abstract_action_parameters *get_parameters(void);
  virtual int get_cap(void);
  void set_active_cap(int cap);
  bool channel_exists(int channel_id);
};

#endif /* ACTIONTRIGGERCONFIG_H_ */
