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

#include "alexa_change_report_throttling.h"

#include "proto.h"

// static
supla_alexa_change_report_throttling
    supla_alexa_change_report_throttling::instance;

int supla_alexa_change_report_throttling::get_default_delay_time(int func) {
  if (func == SUPLA_CHANNELFNC_THERMOSTAT_HEATPOL_HOMEPLUS) {
    // Heatpol send several reports with the old value before the target
    // value is sent, so we add longer delays for them.
    return 2500000;
  }

  return 500000;  // 0.5 sek.
}

supla_alexa_change_report_throttling::supla_alexa_change_report_throttling()
    : supla_http_throttling() {}

supla_alexa_change_report_throttling::~supla_alexa_change_report_throttling(
    void) {}

// static
supla_alexa_change_report_throttling*
supla_alexa_change_report_throttling::get_instance(void) {
  return &instance;
}
