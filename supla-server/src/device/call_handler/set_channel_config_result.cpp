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

#include "device/call_handler/set_channel_config_result.h"

#include <memory>

#include "device.h"

using std::shared_ptr;

supla_ch_set_channel_config_result::supla_ch_set_channel_config_result(void)
    : supla_abstract_device_srpc_call_handler() {}

supla_ch_set_channel_config_result::~supla_ch_set_channel_config_result() {}

bool supla_ch_set_channel_config_result::can_handle_call(unsigned int call_id) {
  return call_id == SUPLA_DS_CALL_SET_CHANNEL_CONFIG_RESULT;
}

void supla_ch_set_channel_config_result::handle_call(
    shared_ptr<supla_device> device, supla_abstract_srpc_adapter* srpc_adapter,
    TsrpcReceivedData* rd, unsigned int call_id, unsigned char proto_version) {
  // This call has no effect
}
