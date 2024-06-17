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

#include "GetHvacValueCommandTest.h"

namespace testing {

void GetHvacValueCommandTest::SetUp() {
  IpcCommandTest::SetUp();
  cmd = new GetHvacValueCommandMock(socketAdapter);
}

void GetHvacValueCommandTest::TearDown() {
  IpcCommandTest::TearDown();
  delete cmd;
}

supla_abstract_ipc_command *GetHvacValueCommandTest::getCommand(void) {
  return cmd;
}

TEST_F(GetHvacValueCommandTest, noData) {
  EXPECT_FALSE(cmd->process_command(buffer, sizeof(buffer), 0));
}

TEST_F(GetHvacValueCommandTest, getHvacValueWithSuccess) {
  char raw_value[SUPLA_CHANNELVALUE_SIZE] = {};
  ((THVACValue *)raw_value)->IsOn = 1;

  supla_channel_hvac_value_with_temphum *hvac =
      new supla_channel_hvac_value_with_temphum(raw_value);
  hvac->set_mode(SUPLA_HVAC_MODE_COOL);
  hvac->set_setpoint_temperature_heat(12345);
  hvac->set_setpoint_temperature_cool(14567);
  hvac->set_temperature(12);
  hvac->set_humidity(34);

  EXPECT_CALL(*cmd, get_hvac_value(10, 20, 30)).WillOnce(Return(hvac));

  commandProcessingTest("GET-HVAC-VALUE:10,20,30\n",
                        "VALUE:1,3,12345,14567,3,12,34\n");
}

TEST_F(GetHvacValueCommandTest, getHvacValueWithoutTemperatureAndHumidity) {
  char raw_value[SUPLA_CHANNELVALUE_SIZE] = {};
  ((THVACValue *)raw_value)->IsOn = 1;

  supla_channel_hvac_value_with_temphum *hvac =
      new supla_channel_hvac_value_with_temphum(raw_value);
  hvac->set_mode(SUPLA_HVAC_MODE_COOL);
  hvac->set_setpoint_temperature_heat(12345);
  hvac->set_setpoint_temperature_cool(14567);

  EXPECT_CALL(*cmd, get_hvac_value(10, 20, 30)).WillOnce(Return(hvac));

  commandProcessingTest("GET-HVAC-VALUE:10,20,30\n",
                        "VALUE:1,3,12345,14567,3,-27300,-100\n");
}

TEST_F(GetHvacValueCommandTest, getHvacValueWithoutHumidity) {
  char raw_value[SUPLA_CHANNELVALUE_SIZE] = {};
  ((THVACValue *)raw_value)->IsOn = 1;

  supla_channel_hvac_value_with_temphum *hvac =
      new supla_channel_hvac_value_with_temphum(raw_value);
  hvac->set_mode(SUPLA_HVAC_MODE_COOL);
  hvac->set_setpoint_temperature_heat(12345);
  hvac->set_setpoint_temperature_cool(14567);
  hvac->set_temperature(123);

  EXPECT_CALL(*cmd, get_hvac_value(10, 20, 30)).WillOnce(Return(hvac));

  commandProcessingTest("GET-HVAC-VALUE:10,20,30\n",
                        "VALUE:1,3,12345,14567,3,123,-100\n");
}

TEST_F(GetHvacValueCommandTest, getHvacValueWithFilure) {
  supla_channel_hvac_value_with_temphum *hvac = nullptr;
  EXPECT_CALL(*cmd, get_hvac_value).WillOnce(Return(hvac));
  commandProcessingTest("GET-HVAC-VALUE:10,20,30\n", "UNKNOWN:30\n");
}

TEST_F(GetHvacValueCommandTest, noParams) {
  EXPECT_CALL(*cmd, get_hvac_value).Times(0);
  commandProcessingTest("GET-HVAC-VALUE:\n", "UNKNOWN:0\n");
}

TEST_F(GetHvacValueCommandTest, paramsWithZeros) {
  EXPECT_CALL(*cmd, get_hvac_value).Times(0);
  commandProcessingTest("GET-HVAC-VALUE:0,0,0\n", "UNKNOWN:0\n");
}

TEST_F(GetHvacValueCommandTest, badParams) {
  EXPECT_CALL(*cmd, get_hvac_value).Times(0);
  commandProcessingTest("GET-HVAC-VALUE:a,10,c\n", "UNKNOWN:0\n");
}

} /* namespace testing */
