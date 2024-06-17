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

#include "ipc/ActionCommandTest.h"

#include "actions/abstract_action_config.h"
#include "proto.h"

namespace testing {

void ActionCommandTest::SetUp() { IpcCommandTest::SetUp(); }

void ActionCommandTest::TearDown() { IpcCommandTest::TearDown(); }

supla_abstract_ipc_command *ActionCommandTest::getCommand(void) { return cmd; }

TEST_F(ActionCommandTest, noData) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_FALSE(cmd->process_command(buffer, sizeof(buffer), 0));
}

TEST_F(ActionCommandTest, OpenWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, true, NULL, NULL))
      .WillOnce(Return(true));

  commandProcessingTest("ACTION-OPEN:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, OpenWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).WillOnce(Return(false));
  commandProcessingTest("ACTION-OPEN:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, OpenWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).Times(0);
  commandProcessingTest("ACTION-OPEN:\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, ActionOpenWithAlexaCorrelationToken) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, true, StrEq("TokenABCD"), NULL))
      .WillOnce(Return(true));

  commandProcessingTest(
      "ACTION-OPEN:10,20,30,ALEXA-CORRELATION-TOKEN=VG9rZW5BQkNE\n", "OK:30\n");
}

TEST_F(ActionCommandTest, ActionOpenWithGoogleRequestId) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, true, NULL, StrEq("RequestID")))
      .WillOnce(Return(true));

  commandProcessingTest("ACTION-OPEN:10,20,30,GOOGLE-REQUEST-ID=UmVxdWVzdElE\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, CloseWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_CLOSE);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, false, NULL, NULL))
      .WillOnce(Return(true));

  commandProcessingTest("ACTION-CLOSE:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, CloseWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_CLOSE);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).WillOnce(Return(false));
  commandProcessingTest("ACTION-CLOSE:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, CloseWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_CLOSE);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).Times(0);
  commandProcessingTest("ACTION-CLOSE:10\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, ActionCloseWithAlexaCorrelationToken) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_CLOSE);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, false, StrEq("TokenABCD"), NULL))
      .WillOnce(Return(true));

  commandProcessingTest(
      "ACTION-CLOSE:10,20,30,ALEXA-CORRELATION-TOKEN=VG9rZW5BQkNE\n",
      "OK:30\n");
}

TEST_F(ActionCommandTest, ActionCloseWithGoogleRequestId) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_CLOSE);
  cmd = &c;
  EXPECT_CALL(c, action_open_close(10, 20, 30, false, NULL, StrEq("RequestID")))
      .WillOnce(Return(true));

  commandProcessingTest(
      "ACTION-CLOSE:10,20,30,GOOGLE-REQUEST-ID=UmVxdWVzdElE\n", "OK:30\n");
}

TEST_F(ActionCommandTest, TurnOnWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_ON);
  cmd = &c;
  EXPECT_CALL(c, action_turn_on(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-TURN-ON:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, TurnOnWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_ON);
  cmd = &c;
  EXPECT_CALL(c, action_turn_on).WillOnce(Return(false));
  commandProcessingTest("ACTION-TURN-ON:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, TurnOnWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_ON);
  cmd = &c;
  EXPECT_CALL(c, action_turn_on).Times(0);
  commandProcessingTest("ACTION-TURN-ON:10\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, TurnOffWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_OFF);
  cmd = &c;
  EXPECT_CALL(c, action_turn_off(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-TURN-OFF:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, TurnOffWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_OFF);
  cmd = &c;
  EXPECT_CALL(c, action_turn_off).WillOnce(Return(false));
  commandProcessingTest("ACTION-TURN-OFF:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, TurnOffWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TURN_OFF);
  cmd = &c;
  EXPECT_CALL(c, action_turn_off).Times(0);
  commandProcessingTest("ACTION-TURN-OFF:10\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, ToggleWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TOGGLE);
  cmd = &c;
  EXPECT_CALL(c, action_toggle(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-TOGGLE:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, ToggleWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TOGGLE);
  cmd = &c;
  EXPECT_CALL(c, action_toggle).WillOnce(Return(false));
  commandProcessingTest("ACTION-TOGGLE:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, ToggleWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_TOGGLE);
  cmd = &c;
  EXPECT_CALL(c, action_toggle).Times(0);
  commandProcessingTest("ACTION-TOGGLE:10\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, StopWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_stop(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-STOP:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, StopWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_stop).WillOnce(Return(false));
  commandProcessingTest("ACTION-STOP:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, StopWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_stop).Times(0);
  commandProcessingTest("ACTION-STOP:10\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, UpOrStopWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_UP_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_up_or_stop(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-UP-OR-STOP:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, UpOrStopWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_UP_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_up_or_stop).WillOnce(Return(false));
  commandProcessingTest("ACTION-UP-OR-STOP:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, UpOrStopWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_UP_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_up_or_stop).Times(0);
  commandProcessingTest("ACTION-UP-OR-STOP:\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, DownOrStopWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_DOWN_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_down_or_stop(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-DOWN-OR-STOP:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, DownOrStopWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_DOWN_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_down_or_stop).WillOnce(Return(false));
  commandProcessingTest("ACTION-DOWN-OR-STOP:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, DownOrStopWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_DOWN_OR_STOP);
  cmd = &c;
  EXPECT_CALL(c, action_down_or_stop).Times(0);
  commandProcessingTest("ACTION-DOWN-OR-STOP:\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, StepByStepWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STEP_BY_STEP);
  cmd = &c;
  EXPECT_CALL(c, action_step_by_step(10, 20, 30)).WillOnce(Return(true));

  commandProcessingTest("ACTION-SBS:10,20,30\n", "OK:30\n");
}

TEST_F(ActionCommandTest, StepByStepWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STEP_BY_STEP);
  cmd = &c;
  EXPECT_CALL(c, action_step_by_step).WillOnce(Return(false));
  commandProcessingTest("ACTION-SBS:10,20,30\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, StepByStepWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_STEP_BY_STEP);
  cmd = &c;
  EXPECT_CALL(c, action_step_by_step).Times(0);
  commandProcessingTest("ACTION-SBS:\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, CopyWithSuccess) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_COPY);
  cmd = &c;
  EXPECT_CALL(c, action_copy(10, 20, 30, 50, 100)).WillOnce(Return(true));

  commandProcessingTest("ACTION-COPY:10,20,30,50,100\n", "OK:30\n");
}

TEST_F(ActionCommandTest, CopyWithSuccessWithoutSourceDeviceId) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_COPY);
  cmd = &c;
  EXPECT_CALL(c, action_copy(10, 20, 30, 0, 100)).WillOnce(Return(true));

  commandProcessingTest("ACTION-COPY:10,20,30,0,100\n", "OK:30\n");
}

TEST_F(ActionCommandTest, CopyWithFilure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_COPY);
  cmd = &c;
  EXPECT_CALL(c, action_copy).WillOnce(Return(false));
  commandProcessingTest("ACTION-COPY:10,20,30,50,100\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, CopyWithoutParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_COPY);
  cmd = &c;
  EXPECT_CALL(c, action_copy).Times(0);
  commandProcessingTest("ACTION-COPY:\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, paramsWithZeros) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).Times(0);
  commandProcessingTest("ACTION-OPEN:0,0,0\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, badParams) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_OPEN);
  cmd = &c;
  EXPECT_CALL(c, action_open_close).Times(0);
  commandProcessingTest("ACTION-OPEN:a,10,c\n", "UNKNOWN:0\n");
}

TEST_F(ActionCommandTest, ShutPartiallyWithDelta) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_SHUT_PARTIALLY);
  cmd = &c;
  EXPECT_CALL(c, action_shut(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_shading_system_parameters *params) {
        EXPECT_EQ(params->get_percentage(), 35);
        EXPECT_EQ(params->get_tilt(), 20);
        EXPECT_EQ(params->get_flags(),
                  SSP_FLAG_PERCENTAGE_AS_DELTA | SSP_FLAG_TILT_AS_DELTA);
        return true;
      });

  commandProcessingTest("ACTION-SHUT-PARTIALLY:10,20,30,35,1,20,1\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, ShutPartiallyWithoutDelta) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_SHUT_PARTIALLY);
  cmd = &c;
  EXPECT_CALL(c, action_shut(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_shading_system_parameters *params) {
        EXPECT_EQ(params->get_percentage(), 35);
        EXPECT_EQ(params->get_tilt(), 11);
        EXPECT_EQ(params->get_flags(), 0);
        return true;
      });

  commandProcessingTest("ACTION-SHUT-PARTIALLY:10,20,30,35,0,11,0\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, ShutPartiallyWithFaulure) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_SHUT_PARTIALLY);
  cmd = &c;
  EXPECT_CALL(c, action_shut(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_shading_system_parameters *params) {
        EXPECT_EQ(params->get_percentage(), 35);
        return false;
      });

  commandProcessingTest("ACTION-SHUT-PARTIALLY:10,20,30,35,0\n", "FAIL:30\n");
}

TEST_F(ActionCommandTest, HvacSetParameters) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_HVAC_SET_PARAMETERS);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_set_parameters(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_hvac_parameters *params) -> bool {
        EXPECT_EQ(params->get_duration_sec(), 1);
        EXPECT_EQ(params->get_mode(), 2);
        EXPECT_EQ(params->get_setpoint_temperature_heat(), 3);
        EXPECT_EQ(params->get_setpoint_temperature_cool(), 4);
        EXPECT_EQ(params->get_flags(), 5);
        return true;
      });

  commandProcessingTest("ACTION-HVAC-SET-PARAMETERS:10,20,30,1,2,3,4,5\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSwitchToManualMode) {
  StrictMock<ActionCommandMock> c(socketAdapter,
                                  ACTION_HVAC_SWITCH_TO_MANUAL_MODE);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_switch_to_manual_mode(10, 20, 30))
      .WillOnce(Return(true));

  commandProcessingTest("ACTION-HVAC-SWITCH-TO-MANUAL-MODE:10,20,30\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSwitchToProgramMode) {
  StrictMock<ActionCommandMock> c(socketAdapter,
                                  ACTION_HVAC_SWITCH_TO_PROGRAM_MODE);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_switch_to_program_mode(10, 20, 30))
      .WillOnce(Return(true));

  commandProcessingTest("ACTION-HVAC-SWITCH-TO-PROGRAM-MODE:10,20,30\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSetTemperature) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_HVAC_SET_TEMPERATURE);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_set_temperature(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_hvac_setpoint_temperature *t) -> bool {
        EXPECT_EQ(t->get_temperature(), -12);
        return true;
      });

  commandProcessingTest("ACTION-HVAC-SET-TEMPERATURE:10,20,30,-12\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSetHeatingTemperature) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_HVAC_SET_TEMPERATURES);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_set_temperatures(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_hvac_setpoint_temperatures *t) -> bool {
        short temperature = 0;
        EXPECT_TRUE(t->get_heating_temperature(&temperature));
        EXPECT_EQ(temperature, 230);
        EXPECT_FALSE(t->get_cooling_temperature(&temperature));
        return true;
      });

  commandProcessingTest("ACTION-HVAC-SET-TEMPERATURES:10,20,30,230,-1,1\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSetCoolingTemperature) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_HVAC_SET_TEMPERATURES);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_set_temperatures(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_hvac_setpoint_temperatures *t) -> bool {
        short temperature = 0;
        EXPECT_FALSE(t->get_heating_temperature(&temperature));
        EXPECT_TRUE(t->get_cooling_temperature(&temperature));
        EXPECT_EQ(temperature, -1);
        return true;
      });

  commandProcessingTest("ACTION-HVAC-SET-TEMPERATURES:10,20,30,230,-1,2\n",
                        "OK:30\n");
}

TEST_F(ActionCommandTest, HvacSetHeatingAndCoolingTemperature) {
  StrictMock<ActionCommandMock> c(socketAdapter, ACTION_HVAC_SET_TEMPERATURES);
  cmd = &c;
  EXPECT_CALL(c, action_hvac_set_temperatures(10, 20, 30, NotNull()))
      .WillOnce([](int user_id, int device_id, int channel_id,
                   const supla_action_hvac_setpoint_temperatures *t) -> bool {
        short temperature = 0;
        EXPECT_TRUE(t->get_heating_temperature(&temperature));
        EXPECT_EQ(temperature, 230);
        EXPECT_TRUE(t->get_cooling_temperature(&temperature));
        EXPECT_EQ(temperature, -1);
        return true;
      });

  commandProcessingTest("ACTION-HVAC-SET-TEMPERATURES:10,20,30,230,-1,3\n",
                        "OK:30\n");
}

} /* namespace testing */
