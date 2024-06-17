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

#ifndef ACTIONTRIGGERCONFIGTEST_H_
#define ACTIONTRIGGERCONFIGTEST_H_

#include "gtest/gtest.h"  // NOLINT
#include "jsonconfig/channel/action_trigger_config.h"
#include "proto.h"

namespace testing {

class ActionTriggerConfigTest : public Test {
 protected:
  template <class resultCls>
  resultCls *get_params(action_trigger_config *config);

 public:
  ActionTriggerConfigTest(void);
  virtual ~ActionTriggerConfigTest(void);
  void EXPECT_NO_PARAMS(action_trigger_config *config);
  TAction_ShadingSystem_Parameters get_ss_params(action_trigger_config *config);
  TAction_RGBW_Parameters get_rgbw_params(action_trigger_config *config);
};

} /* namespace testing */

#endif /* ACTIONTRIGGERCONFIGTEST_H_ */
