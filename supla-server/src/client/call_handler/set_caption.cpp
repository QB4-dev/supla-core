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

#include "client/call_handler/set_caption.h"

#include <memory>

#include "client/client.h"
#include "user/user.h"

using std::shared_ptr;

supla_ch_set_caption::supla_ch_set_caption(void)
    : supla_abstract_client_srpc_call_handler() {}

supla_ch_set_caption::~supla_ch_set_caption() {}

bool supla_ch_set_caption::can_handle_call(unsigned int call_id) {
  return call_id == SUPLA_DCS_CALL_SET_CHANNEL_CAPTION ||
         call_id == SUPLA_CS_CALL_SET_CHANNEL_GROUP_CAPTION ||
         call_id == SUPLA_CS_CALL_SET_LOCATION_CAPTION ||
         call_id == SUPLA_CS_CALL_SET_SCENE_CAPTION;
}

void supla_ch_set_caption::handle_call(
    shared_ptr<supla_client> client, supla_abstract_srpc_adapter* srpc_adapter,
    TsrpcReceivedData* rd, unsigned int call_id, unsigned char proto_version) {
  if (rd->data.dcs_set_caption != nullptr) {
    unsigned int limit =
        call_id == SUPLA_CS_CALL_SET_SCENE_CAPTION ||
                call_id == SUPLA_CS_CALL_SET_CHANNEL_GROUP_CAPTION
            ? 256U
            : 101U;

    if (rd->data.dcs_set_caption->CaptionSize > limit) {
      // ! The field in the database is limited to 100/255 characters !
      rd->data.dcs_set_caption->CaptionSize = limit;
    } else if (rd->data.dcs_set_caption->CaptionSize == 0) {
      rd->data.dcs_set_caption->CaptionSize = 1;
    }

    rd->data.dcs_set_caption
        ->Caption[rd->data.dcs_set_caption->CaptionSize - 1] = 0;

    client->get_user()->set_caption(
        supla_caller(ctClient, client->get_id()),
        client->is_superuser_authorized(), rd->data.dcs_set_caption->ID,
        client->get_connection()->get_srpc_adapter()->get_srpc(),
        rd->data.dcs_set_caption, call_id, false);
  }
}
