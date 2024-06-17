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

#include "OnChannelConfigChangedCommandTest.h"

namespace testing {

void OnChannelConfigChangedCommandTest::SetUp() {
  IpcCommandTest::SetUp();
  cmd = new OnChannelConfigChangedCommandMock(socketAdapter);
}

void OnChannelConfigChangedCommandTest::TearDown() {
  IpcCommandTest::TearDown();
  delete cmd;
}

supla_abstract_ipc_command *OnChannelConfigChangedCommandTest::getCommand(
    void) {
  return cmd;
}

TEST_F(OnChannelConfigChangedCommandTest, noData) {
  EXPECT_FALSE(cmd->process_command(buffer, sizeof(buffer), 0));
}

TEST_F(OnChannelConfigChangedCommandTest, channelConfigChanged) {
  EXPECT_CALL(*cmd, on_channel_config_changed(10, 20, 30, 1, 2, 3));

  commandProcessingTest("USER-ON-CHANNEL-CONFIG-CHANGED:10,20,30,1,2,3\n",
                        "OK:10\n");
}

TEST_F(OnChannelConfigChangedCommandTest, noParams) {
  EXPECT_CALL(*cmd, on_channel_config_changed).Times(0);
  commandProcessingTest("USER-ON-CHANNEL-CONFIG-CHANGED:\n", "UNKNOWN:0\n");
}

TEST_F(OnChannelConfigChangedCommandTest, paramsWithZero) {
  EXPECT_CALL(*cmd, on_channel_config_changed).Times(0);
  commandProcessingTest("USER-ON-CHANNEL-CONFIG-CHANGED:10,20,0,1,2,3\n",
                        "UNKNOWN:10\n");
}

TEST_F(OnChannelConfigChangedCommandTest, paramsWithZeros) {
  EXPECT_CALL(*cmd, on_channel_config_changed).Times(0);
  commandProcessingTest("USER-ON-CHANNEL-CONFIG-CHANGED:0,0,0,0,0,0\n",
                        "UNKNOWN:0\n");
}

TEST_F(OnChannelConfigChangedCommandTest, badParams) {
  EXPECT_CALL(*cmd, on_channel_config_changed).Times(0);
  commandProcessingTest("USER-ON-CHANNEL-CONFIG-CHANGED:a,10,30,1,2,3\n",
                        "UNKNOWN:0\n");
}

} /* namespace testing */
