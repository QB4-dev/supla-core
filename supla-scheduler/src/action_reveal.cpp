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

#include "action_reveal.h"

#include <stdlib.h>
#include <string.h>

#include "json/cJSON.h"
#include "log.h"

s_worker_action_reveal::s_worker_action_reveal(s_abstract_worker *worker)
    : s_abstract_action_shut_partially(worker) {}

s_worker_action_reveal::~s_worker_action_reveal(void) {}

bool s_worker_action_reveal::get_expected(char *percentage,
                                          bool *percentage_as_delta, char *tilt,
                                          bool *tilt_as_delta) {
  if (percentage == nullptr || percentage_as_delta == nullptr ||
      tilt == nullptr || tilt_as_delta == nullptr) {
    return false;
  }

  *percentage = 0;
  *percentage_as_delta = false;
  *tilt = -1;
  *tilt_as_delta = false;

  return true;
}

REGISTER_ACTION(s_worker_action_reveal, ACTION_REVEAL);
