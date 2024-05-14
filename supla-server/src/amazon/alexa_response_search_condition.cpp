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

#include "amazon/alexa_response_search_condition.h"

#include "amazon/alexa_response_request.h"

supla_alexa_response_search_condition::supla_alexa_response_search_condition(
    int user_id, int device_id, int channel_id, bool not_postponed) {
  this->user_id = user_id;
  this->device_id = device_id;
  this->channel_id = channel_id;
  this->not_postponed = not_postponed;
}

bool supla_alexa_response_search_condition::condition_met(
    supla_abstract_asynctask *task) {
  supla_alexa_response_request *request =
      dynamic_cast<supla_alexa_response_request *>(task);
  return request && request->get_user_id() == user_id &&
         request->get_device_id() == device_id &&
         request->get_channel_id() == channel_id &&
         request->get_state() == supla_asynctask_state::WAITING &&
         (!not_postponed || !request->is_postponed());
}
