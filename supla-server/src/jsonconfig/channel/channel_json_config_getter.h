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

#ifndef CHANNELJSONCONFIGGETTER_H_
#define CHANNELJSONCONFIGGETTER_H_

#include "jsonconfig/abstract_json_config_getter.h"

class channel_json_config_getter : public abstract_json_config_getter {
 private:
 protected:
 public:
  channel_json_config_getter(void);
  virtual ~channel_json_config_getter(void);

  virtual supla_json_config *get_config(int user_id, int device_id,
                                        int channel_id);
};

#endif /* CHANNELJSONCONFIGGETTER_H_ */
