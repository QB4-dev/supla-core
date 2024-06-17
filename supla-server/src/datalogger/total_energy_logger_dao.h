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

#ifndef TOTAL_ENERGY_LOGGER_DAO_H_
#define TOTAL_ENERGY_LOGGER_DAO_H_

#include "db/abstract_db_access_provider.h"
#include "proto.h"

class supla_total_energy_logger_dao {
 private:
  supla_abstract_db_access_provider *dba;
  void set_longlong(unsigned _supla_int64_t *v, void *pbind,
                    bool *not_null_flag);

 public:
  explicit supla_total_energy_logger_dao(
      supla_abstract_db_access_provider *dba);
  void add(int channel_id, TElectricityMeter_ExtendedValue_V2 *em_ev);
};

#endif /* TOTAL_ENERGY_LOGGER_DAO_H_ */
