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

#include <ipc/on_scene_removed_command.h>

#include "user.h"

supla_on_scene_removed_command::supla_on_scene_removed_command(
    supla_abstract_ipc_socket_adapter *socket_adapter)
    : supla_abstract_on_scene_removed_command(socket_adapter) {}

void supla_on_scene_removed_command::on_scene_removed(int user_id,
                                                      int scene_id) {
  supla_user::on_scene_removed(get_caller(), user_id, scene_id);
}
