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

#ifndef ACTIONCONFIGTEST_H_
#define ACTIONCONFIGTEST_H_

#include "actions/action_config.h"
#include "gtest/gtest.h"  // NOLINT

namespace testing {

class ActionConfigTest : public Test {
 protected:
  supla_action_config config;

 public:
  ActionConfigTest(void);
  virtual ~ActionConfigTest(void);

  char get_percentage_and_tilt(char *tile);
  void set_percentage_and_tilt(supla_action_config *config, char percentage,
                               char tilt);
  TAction_RGBW_Parameters get_rgbw(void);
  void set_rgbw(supla_action_config *config,
                const TAction_RGBW_Parameters &rgbw);
};

} /* namespace testing */

#endif /* ACTIONCONFIGTEST_H_ */
