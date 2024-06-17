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

#ifndef CLIENT_CLIENTCHANNELGROUPRELATION_H_
#define CLIENT_CLIENTCHANNELGROUPRELATION_H_

#include "clientobjcontaineritem.h"

class supla_client;
class supla_client_channelgroups;
class supla_client_channelgroup_relation
    : public supla_client_objcontainer_item {
 private:
  int GroupId;
  int DeviceId;

 protected:
 public:
  supla_client_channelgroup_relation(supla_client_channelgroups *Container,
                                     int DeviceId, int ChannelId, int GroupId);
  bool remote_update_is_possible(void);
  int get_extra_id(void);
  int getDeviceId(void);
  int getChannelId(void);
  int getGroupId(void);
  void proto_get(TSC_SuplaChannelGroupRelation *group_relation);
};

#endif /* CLIENT_CLIENTCHANNELGROUPRELATION_H_ */
