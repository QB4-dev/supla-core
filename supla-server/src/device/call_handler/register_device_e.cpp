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

#include "call_handler/register_device_e.h"

#include <stdlib.h>
#include <string.h>

#include <memory>

#include "log.h"
#include "proto.h"
#include "srpc/abstract_srpc_call_hanlder_collection.h"

using std::shared_ptr;

supla_ch_register_device_e::supla_ch_register_device_e(void)
    : supla_abstract_device_srpc_call_handler() {}

supla_ch_register_device_e::~supla_ch_register_device_e() {}

bool supla_ch_register_device_e::is_registration_required(void) {
  return false;
}

bool supla_ch_register_device_e::can_handle_call(unsigned int call_id) {
  return call_id == SUPLA_DS_CALL_REGISTER_DEVICE_E;
}

void supla_ch_register_device_e::handle_call(
    shared_ptr<supla_device> device, supla_abstract_srpc_adapter* srpc_adapter,
    TsrpcReceivedData* rd, unsigned int call_id, unsigned char proto_version) {
  supla_log(LOG_DEBUG, "SUPLA_DS_CALL_REGISTER_DEVICE_E");

  if (rd->data.ds_register_device_e != nullptr) {
    TDS_SuplaRegisterDevice_F* register_device_f =
        (TDS_SuplaRegisterDevice_F*)malloc(sizeof(TDS_SuplaRegisterDevice_F));
    if (register_device_f != nullptr) {
      memset(register_device_f, 0, sizeof(TDS_SuplaRegisterDevice_E));

      memcpy(register_device_f->Email, rd->data.ds_register_device_e->Email,
             SUPLA_EMAIL_MAXSIZE);
      memcpy(register_device_f->AuthKey, rd->data.ds_register_device_e->AuthKey,
             SUPLA_AUTHKEY_SIZE);

      memcpy(register_device_f->GUID, rd->data.ds_register_device_e->GUID,
             SUPLA_GUID_SIZE);
      memcpy(register_device_f->Name, rd->data.ds_register_device_e->Name,
             SUPLA_DEVICE_NAME_MAXSIZE);
      memcpy(register_device_f->SoftVer, rd->data.ds_register_device_e->SoftVer,
             SUPLA_SOFTVER_MAXSIZE);
      memcpy(register_device_f->ServerName,
             rd->data.ds_register_device_e->ServerName,
             SUPLA_SERVER_NAME_MAXSIZE);

      register_device_f->Flags = rd->data.ds_register_device_e->Flags;
      register_device_f->ManufacturerID =
          rd->data.ds_register_device_e->ManufacturerID;
      register_device_f->ProductID = rd->data.ds_register_device_e->ProductID;

      register_device_f->channel_count =
          rd->data.ds_register_device_e->channel_count;

      for (int c = 0; c < register_device_f->channel_count; c++) {
        memset(&register_device_f->channels[c], 0,
               sizeof(TDS_SuplaDeviceChannel_C));
        register_device_f->channels[c].Number =
            rd->data.ds_register_device_e->channels[c].Number;
        register_device_f->channels[c].Type =
            rd->data.ds_register_device_e->channels[c].Type;
        register_device_f->channels[c].FuncList =
            rd->data.ds_register_device_e->channels[c].FuncList;
        register_device_f->channels[c].Default =
            rd->data.ds_register_device_e->channels[c].Default;
        register_device_f->channels[c].Flags =
            rd->data.ds_register_device_e->channels[c].Flags;
        memcpy(register_device_f->channels[c].value,
               rd->data.ds_register_device_e->channels[c].value,
               SUPLA_CHANNELVALUE_SIZE);
      }

      free(rd->data.ds_register_device_e);
      rd->data.ds_register_device_f = register_device_f;

      device->get_srpc_call_handler_collection()->handle_call(
          device, srpc_adapter, rd, SUPLA_DS_CALL_REGISTER_DEVICE_F,
          proto_version);
    }
  }
}
