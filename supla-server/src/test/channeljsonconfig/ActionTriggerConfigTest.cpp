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

#include "ActionTriggerConfigTest.h"

#include "TestHelper.h"
#include "channeljsonconfig/actiontriggerconfig.h"
#include "proto.h"

namespace testing {

ActionTriggerConfigTest::ActionTriggerConfigTest(void) {}
ActionTriggerConfigTest::~ActionTriggerConfigTest(void) {}

TEST_F(ActionTriggerConfigTest, root) {
  channel_json_config *c1 = new channel_json_config();
  action_trigger_config *c2 = new action_trigger_config(c1);

  EXPECT_TRUE(c1 != NULL);

  if (!c1 || !c2) {
    if (c1) {
      delete c1;
    }

    if (c2) {
      delete c2;
    }
  }

  char *str1 = c1->get_config();
  EXPECT_TRUE(str1 != NULL);

  if (str1) {
    EXPECT_EQ(strncmp(str1, "{}", 5), 0);
    free(str1);
    str1 = NULL;
  }

  str1 = c2->get_config();
  EXPECT_TRUE(str1 != NULL);

  if (str1) {
    EXPECT_EQ(strncmp(str1, "{}", 5), 0);
    free(str1);
    str1 = NULL;
  }

  c2->set_capabilities(SUPLA_ACTION_CAP_HOLD);

  str1 = c1->get_config();
  EXPECT_TRUE(str1 != NULL);

  char *str2 = c2->get_config();
  EXPECT_TRUE(str2 != NULL);

  if (str1 && str2) {
    EXPECT_NE(strncmp(str1, "{}", 5), 0);
    EXPECT_EQ(strncmp(str1, str2, 1000), 0);
  }

  if (str1) {
    free(str1);
    str1 = NULL;
  }

  if (str2) {
    free(str2);
    str2 = NULL;
  }

  delete c1;
  delete c2;
}

TEST_F(ActionTriggerConfigTest, allCaps) {
  action_trigger_config *config = new action_trigger_config();
  ASSERT_TRUE(config != NULL);

  EXPECT_TRUE(config->set_capabilities(0xFFFFFFFF));
  EXPECT_FALSE(config->set_capabilities(0xFFFFFFFF));

  unsigned int all =
      SUPLA_ACTION_CAP_TURN_ON | SUPLA_ACTION_CAP_TURN_OFF |
      SUPLA_ACTION_CAP_TOGGLE_x1 | SUPLA_ACTION_CAP_TOGGLE_x2 |
      SUPLA_ACTION_CAP_TOGGLE_x3 | SUPLA_ACTION_CAP_TOGGLE_x4 |
      SUPLA_ACTION_CAP_TOGGLE_x5 | SUPLA_ACTION_CAP_HOLD |
      SUPLA_ACTION_CAP_SHORT_PRESS_x1 | SUPLA_ACTION_CAP_SHORT_PRESS_x2 |
      SUPLA_ACTION_CAP_SHORT_PRESS_x3 | SUPLA_ACTION_CAP_SHORT_PRESS_x4 |
      SUPLA_ACTION_CAP_SHORT_PRESS_x5;

  EXPECT_EQ(config->get_capabilities(), all);

  char *str = config->get_config();
  EXPECT_TRUE(str != NULL);

  if (str) {
    // TestHelper::printEscaped(str);
    EXPECT_EQ(
        strncmp(
            str,
            "{\"actionTriggerCapabilities\":[\"TURN_ON\",\"TURN_OFF\",\"TOGGLE_"
            "X1\",\"TOGGLE_X2\",\"TOGGLE_X3\",\"TOGGLE_X4\",\"TOGGLE_X5\","
            "\"HOLD\",\"SHORT_PRESS_X1\",\"SHORT_PRESS_X2\",\"SHORT_PRESS_"
            "X3\",\"SHORT_PRESS_X4\",\"SHORT_PRESS_X5\"]}",
            1000),
        0);
    free(str);
    str = NULL;
  }

  delete config;
}

TEST_F(ActionTriggerConfigTest, amodificationAmongOtherParameters) {
  action_trigger_config *config = new action_trigger_config();
  ASSERT_TRUE(config != NULL);

  config->set_config("{\"a\":true}");

  EXPECT_TRUE(config->set_capabilities(SUPLA_ACTION_CAP_TOGGLE_x2));
  EXPECT_FALSE(config->set_capabilities(SUPLA_ACTION_CAP_TOGGLE_x2));

  char *str = config->get_config();
  EXPECT_TRUE(str != NULL);

  if (str) {
    // TestHelper::printEscaped(str);

    EXPECT_EQ(
        strncmp(str,
                "{\"a\":true,\"actionTriggerCapabilities\":[\"TOGGLE_X2\"]}",
                1000),
        0);

    free(str);
    str = NULL;
  }

  config->set_config(
      "{\"actionTriggerCapabilities\":[\"TOGGLE_X3\"],\"a\":true}");
  EXPECT_EQ(config->get_capabilities(),
            (unsigned int)SUPLA_ACTION_CAP_TOGGLE_x3);

  EXPECT_FALSE(config->set_capabilities(SUPLA_ACTION_CAP_TOGGLE_x3));

  str = config->get_config();
  EXPECT_TRUE(str != NULL);

  if (str) {
    // TestHelper::printEscaped(str);

    EXPECT_EQ(
        strncmp(str,
                "{\"actionTriggerCapabilities\":[\"TOGGLE_X3\"],\"a\":true}",
                1000),
        0);

    free(str);
    str = NULL;
  }

  EXPECT_TRUE(config->set_capabilities(SUPLA_ACTION_CAP_TOGGLE_x3 |
                                       SUPLA_ACTION_CAP_TOGGLE_x1 |
                                       SUPLA_ACTION_CAP_TOGGLE_x4));

  str = config->get_config();
  EXPECT_TRUE(str != NULL);

  if (str) {
    // TestHelper::printEscaped(str);

    EXPECT_EQ(
        strncmp(str,
                "{\"actionTriggerCapabilities\":[\"TOGGLE_X1\",\"TOGGLE_X3\","
                "\"TOGGLE_X4\"],\"a\":true}",
                1000),
        0);

    free(str);
    str = NULL;
  }

  delete config;
}

TEST_F(ActionTriggerConfigTest, readActiveTriggers) {
  action_trigger_config *config = new action_trigger_config();
  ASSERT_TRUE(config != NULL);

  config->set_config(
      "{\"actions\":{\"SHORT_PRESS_X5\":{\"subjectId\":1,\"subjectType\":"
      "\"channel\",\"action\":{\"id\":10,\"param\":[]}},\"HOLD\":{"
      "\"subjectId\":1,\"subjectType\":\"scene\",\"action\":{\"id\":3000,"
      "\"param\":[]}}}}");

  EXPECT_EQ(config->get_active_actions(), (unsigned int)0);

  config->set_config(
      "{\"actions\":{\"SHORT_PRESS_X5\":{\"subjectId\":1,\"subjectType\":"
      "\"channel\",\"action\":{\"id\":10,\"param\":[]}},\"HOLD\":{"
      "\"subjectId\":1,\"subjectType\":\"scene\",\"action\":{\"id\":3000,"
      "\"param\":[]}}},\"actionTriggerCapabilities\":[\"HOLD\"]}");

  EXPECT_EQ(config->get_active_actions(), (unsigned int)SUPLA_ACTION_CAP_HOLD);

  config->set_config(
      "{\"actions\":{\"SHORT_PRESS_X5\":{\"subjectId\":1,\"subjectType\":"
      "\"channel\",\"action\":{\"id\":10,\"param\":[]}},\"HOLD\":{"
      "\"subjectId\":1,\"subjectType\":\"scene\",\"action\":{\"id\":3000,"
      "\"param\":[]}}},\"actionTriggerCapabilities\":[\"HOLD\", "
      "\"SHORT_PRESS_X1\", "
      "\"SHORT_PRESS_X5\"]}");

  EXPECT_EQ(
      config->get_active_actions(),
      (unsigned int)(SUPLA_ACTION_CAP_SHORT_PRESS_x5 | SUPLA_ACTION_CAP_HOLD));

  delete config;
}

} /* namespace testing */
