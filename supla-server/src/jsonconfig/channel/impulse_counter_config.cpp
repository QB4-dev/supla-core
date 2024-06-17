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

#include "impulse_counter_config.h"

#include <limits.h>

#include "srpc/srpc.h"

#define INITIAL_VALUE_MIN -100000000
#define INITIAL_VALUE_MAX 100000000
#define IMPULSES_PER_UNIT_MIN 0
#define IMPULSES_PER_UNIT_MAX 1000000

// static
const char impulse_counter_config::initial_value_key[] = "initialValue";

// static
const char impulse_counter_config::impulses_per_unit_key[] = "impulsesPerUnit";

// static
const char impulse_counter_config::add_to_history_key[] = "addToHistory";

impulse_counter_config::impulse_counter_config(void) : supla_json_config() {}

impulse_counter_config::impulse_counter_config(supla_json_config *root)
    : supla_json_config(root) {}

bool impulse_counter_config::should_be_added_to_history(void) {
  cJSON *root = get_user_root();
  if (!root) {
    return 0;
  }

  cJSON *item = cJSON_GetObjectItem(root, add_to_history_key);
  return item && cJSON_IsBool(item) && cJSON_IsTrue(item);
}

double impulse_counter_config::get_double_value(const char *key, double min,
                                                double max) {
  cJSON *root = get_user_root();
  if (!root) {
    return 0;
  }

  cJSON *initial_value = cJSON_GetObjectItem(root, key);
  if (initial_value && cJSON_IsNumber(initial_value)) {
    if (initial_value->valuedouble > max) {
      return max;
    } else if (initial_value->valuedouble < min) {
      return min;
    }
    return initial_value->valuedouble;
  }

  return 0;
}

double impulse_counter_config::get_initial_value(void) {
  return get_double_value(initial_value_key, INITIAL_VALUE_MIN,
                          INITIAL_VALUE_MAX);
}

unsigned int impulse_counter_config::get_impulses_per_unit(void) {
  return get_double_value(impulses_per_unit_key, IMPULSES_PER_UNIT_MIN,
                          IMPULSES_PER_UNIT_MAX);
}

void impulse_counter_config::add_initial_value(
    unsigned _supla_int64_t *counter) {
  if (!counter) {
    return;
  }

  unsigned _supla_int64_t left = ULONG_MAX - (*counter);
  double initial_value = get_initial_value();
  int impulses_per_unit = get_impulses_per_unit();

  if (initial_value == 0 || impulses_per_unit == 0) {
    return;
  }

  bool minus = false;
  if (initial_value < 0) {
    minus = true;
    initial_value *= -1;
  }

  unsigned _supla_int64_t impulses_added = initial_value * impulses_per_unit;

  if (minus) {
    if (impulses_added > (*counter)) {
      impulses_added = (*counter);
    }
    *counter -= impulses_added;
  } else {
    if (impulses_added > left) {
      impulses_added = left;
    }
    *counter += impulses_added;
  }
}
