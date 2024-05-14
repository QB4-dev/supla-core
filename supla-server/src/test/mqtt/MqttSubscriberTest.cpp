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

#include "MqttSubscriberTest.h"

#include "log.h"  // NOLINT
#include "mqtt_subscriber.h"
#include "mqtt_subscriber_datasource.h"

namespace testing {

MqttSubscriberTest::MqttSubscriberTest() : MqttClientTest() {
  value_setter = NULL;
}

MqttSubscriberTest::~MqttSubscriberTest() {}

void MqttSubscriberTest::waitForData(int expectedTopicCount) {
  for (int a = 0; a < 5000; a++) {
    if (getLibAdapter()->subscribed_count() == expectedTopicCount &&
        !getDS()->is_context_open()) {
      return;
    }
    usleep(1000);
  }

  EXPECT_EQ(getLibAdapter()->subscribed_count(), expectedTopicCount);
  EXPECT_TRUE(getDS()->is_context_open());
  ASSERT_TRUE(false);
}

supla_mqtt_client *MqttSubscriberTest::clientInit(
    supla_mqtt_client_library_adapter *library_adapter,
    supla_mqtt_client_settings *settings,
    supla_mqtt_client_datasource *datasource) {
  value_setter = new MqttValueSetterMock(settings);
  return new supla_mqtt_subscriber(library_adapter, settings, datasource,
                                   value_setter);
}

void MqttSubscriberTest::TearDown() {
  if (value_setter != NULL) {
    delete value_setter;
    value_setter = NULL;
  }

  MqttClientTest::TearDown();
}

MqttValueSetterMock *MqttSubscriberTest::getValueSetter(void) {
  return value_setter;
}

supla_mqtt_client_datasource *MqttSubscriberTest::dsInit(
    supla_mqtt_client_settings *settings) {
  return new supla_mqtt_subscriber_datasource(settings);
}

TEST_F(MqttSubscriberTest, fullScope) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getLibAdapter()->subscribed_pop().compare(
                "supla/+/devices/+/channels/+/set/+"),
            0);
  ASSERT_EQ(getLibAdapter()->subscribed_pop().compare(
                "supla/+/devices/+/channels/+/execute_action"),
            0);

  ASSERT_EQ(
      getLibAdapter()->subscribed_pop().compare("supla/+/refresh_request"), 0);
}

TEST_F(MqttSubscriberTest, refreshRequest) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/refresh_request", "AlL_ExISTiNG");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(0));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getRefreshAllExistingCounter(), 1);
}

TEST_F(MqttSubscriberTest, deviceAndChannelId) {
  waitForConnection();
  waitForData(3);

  ASSERT_TRUE(getValueSetter()->channelEqualTo(0));

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/5/channels/1/set/on",
      "1");

  ASSERT_TRUE(getValueSetter()->deviceEqualTo(5));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1));

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/56/channels/12/set/on",
      "12");

  ASSERT_TRUE(getValueSetter()->deviceEqualTo(56));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(12));

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/143/channels/123/set/on",
      "123");

  ASSERT_TRUE(getValueSetter()->deviceEqualTo(143));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(123));

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/560/channels/-1/set/on",
      "1");

  ASSERT_TRUE(getValueSetter()->deviceEqualTo(560));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(-1));
}

TEST_F(MqttSubscriberTest, email) {
  waitForConnection();
  waitForData(3);

  ASSERT_TRUE(getValueSetter()->suidEqualTo(NULL));

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1/set/on",
      "1");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));

  getLibAdapter()->on_message_received("supla/77/devices/10/channels/1/set/on",
                                       "1");

  ASSERT_TRUE(getValueSetter()->suidEqualTo("77"));
}

TEST_F(MqttSubscriberTest, setOnWithoutPrefix) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/on",
      "1");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 1);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/9/channels/1234/set/on",
      "YeS");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 2);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/on",
      "tRuE");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 3);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/100/channels/1234/set/on",
      "tRuE!");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 3);
}

TEST_F(MqttSubscriberTest, setOnWithPrefix) {
  waitForConnection();
  waitForData(3);

  char prefix[] = "prefix/123";
  getSettings()->setPrefixPtr(prefix);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "prefix/123/supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/"
      "1234/set/on",
      "1");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 1);
}

TEST_F(MqttSubscriberTest, setOff) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/500/channels/1234/set/on",
      "0");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 1);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/100000/channels/1234/set/"
      "on",
      "nO");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 2);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/on",
      "FaLsE");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 3);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/on",
      "F!LsE");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 3);
}

TEST_F(MqttSubscriberTest, turnOn) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "TuRn_On");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOnCounter(), 1);
}

TEST_F(MqttSubscriberTest, turnOff) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707D/devices/10/channels/1234/"
      "execute_action",
      "TuRn_OfF");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707D"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 1);
}

TEST_F(MqttSubscriberTest, off) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707D/devices/10/channels/1234/"
      "execute_action",
      "off");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707D"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOffCounter(), 1);
}

TEST_F(MqttSubscriberTest, toggle) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720/devices/10/channels/1234/execute_action", "tOgGle");

  ASSERT_TRUE(getValueSetter()->suidEqualTo("7720"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getToggleCounter(), 1);
}

TEST_F(MqttSubscriberTest, shut) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "sHuT");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
}

TEST_F(MqttSubscriberTest, reveal) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "rEvEal");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getRevealCounter(), 1);
}

TEST_F(MqttSubscriberTest, up) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "Up");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getUpCounter(), 1);
}

TEST_F(MqttSubscriberTest, down) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "DoWn");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getDownCounter(), 1);
}

TEST_F(MqttSubscriberTest, upOrStop) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "Up_Or_Stop");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getUpOrStopCounter(), 1);
}

TEST_F(MqttSubscriberTest, downOrStop) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "Down_Or_Stop");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getDownOrStopCounter(), 1);
}

TEST_F(MqttSubscriberTest, stepByStep) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "Step_By_StEP");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getStepByStepCounter(), 1);
}

TEST_F(MqttSubscriberTest, stop) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "StOp");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getStopCounter(), 1);
}

TEST_F(MqttSubscriberTest, open) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "oPeN");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOpenCounter(), 1);
}

TEST_F(MqttSubscriberTest, close) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "ClOsE");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getCloseCounter(), 1);
}

TEST_F(MqttSubscriberTest, openClose) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "oPeN_cLoSe");

  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getOpenCloseCounter(), 1);
}

TEST_F(MqttSubscriberTest, setClosingPercentage) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "34.56");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 34);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_tilt(), -1);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "-10");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "0");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "33");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 2);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 33);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "100");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 3);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 100);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "closing_percentage",
      "110");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 0);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);
}

TEST_F(MqttSubscriberTest, setOpeningPercentage) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "45.6789");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 55);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "-10");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "0");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 100);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "33");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 2);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 67);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "100");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 3);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), 0);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "opening_percentage",
      "110");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 0);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);
}

TEST_F(MqttSubscriberTest, setTilt) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "34.56");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), -1);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_tilt(), 34);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "-10");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "0");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 1);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), -1);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_tilt(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "33");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 2);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), -1);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_tilt(), 33);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "100");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 3);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_TRUE(getValueSetter()->getShadingSystemParams() != nullptr);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_percentage(), -1);
  ASSERT_EQ(getValueSetter()->getShadingSystemParams()->get_tilt(), 100);

  getValueSetter()->clear();

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "tilt",
      "110");

  ASSERT_EQ(getValueSetter()->getShutCounter(), 0);
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  EXPECT_TRUE(getValueSetter()->getShadingSystemParams() == nullptr);
}

TEST_F(MqttSubscriberTest, setBrightness) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  ASSERT_EQ(getValueSetter()->getBrightness(), -1);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "33.33abcd");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "-1");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "110");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "12.34");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getBrightnessCounter(), 1);
  ASSERT_EQ(getValueSetter()->getBrightness(), 12);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "0");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getBrightnessCounter(), 2);
  ASSERT_EQ(getValueSetter()->getBrightness(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "brightness",
      "100");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getBrightnessCounter(), 3);
  ASSERT_EQ(getValueSetter()->getBrightness(), 100);
}

TEST_F(MqttSubscriberTest, setColorBrightness) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  ASSERT_EQ(getValueSetter()->getColorBrightness(), -1);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "33,33");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "-1");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "101");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "12.34");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorBrightnessCounter(), 1);
  ASSERT_EQ(getValueSetter()->getColorBrightness(), 12);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "0");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorBrightnessCounter(), 2);
  ASSERT_EQ(getValueSetter()->getColorBrightness(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color_brightness",
      "100");

  ASSERT_TRUE(getValueSetter()->channelEqualTo(1234));
  ASSERT_TRUE(
      getValueSetter()->suidEqualTo("7720767494dd87196e1896c7cbab707c"));
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorBrightnessCounter(), 3);
  ASSERT_EQ(getValueSetter()->getColorBrightness(), 100);
}

TEST_F(MqttSubscriberTest, setColor) {
  waitForConnection();
  waitForData(3);

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0x01FFFFFF);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0xFF00FFa");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "#FF00FFa");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0xFF00FG");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "#FF00FG");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "#FFFFFF");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 1);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xFFFFFF);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "#000000");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 2);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "#AABBCC");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 3);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xAABBCC);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0xFFFFFF");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 4);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xFFFFFF);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0x000000");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 5);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0xAABBCC");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 6);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xAABBCC);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0xAA05CC");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 7);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xAA05CC);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "255,255,255");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 8);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xFFFFFF);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "0,0,0");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 9);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0x000000);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "170,187,204");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 10);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xAABBCC);

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "color",
      "170,5,204");
  ASSERT_EQ(getValueSetter()->counterSetCount(), 1);
  ASSERT_EQ(getValueSetter()->getColorCounter(), 11);
  ASSERT_EQ(getValueSetter()->getColor(), (unsigned int)0xAA05CC);
}

TEST_F(MqttSubscriberTest, setTemperatureSetpointHeat) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperatures(NotNull()))
      .WillOnce([](supla_action_hvac_setpoint_temperatures *temperatures) {
        short t = 0;
        EXPECT_FALSE(temperatures->get_cooling_temperature(&t));
        EXPECT_TRUE(temperatures->get_heating_temperature(&t));
        EXPECT_EQ(t, 2234);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "temperature_setpoint_heat",
      "22.34");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, setTemperatureSetpointCool) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperatures(NotNull()))
      .WillOnce([](supla_action_hvac_setpoint_temperatures *temperatures) {
        short t = 0;
        EXPECT_FALSE(temperatures->get_heating_temperature(&t));
        EXPECT_TRUE(temperatures->get_cooling_temperature(&t));

        EXPECT_EQ(t, 123);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "temperature_setpoint_cool",
      "1.23");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, setTemperatureSetpoint) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperatures).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature(NotNull()))
      .WillOnce([](supla_action_hvac_setpoint_temperature *temperature) {
        EXPECT_EQ(temperature->get_temperature(), 123);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/set/"
      "temperature_setpoint",
      "1.23");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, _auto) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_parameters(NotNull()))
      .WillOnce([](supla_action_hvac_parameters *params) {
        EXPECT_EQ(params->get_mode(), SUPLA_HVAC_MODE_CMD_WEEKLY_SCHEDULE);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "auto");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, heat) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_parameters(NotNull()))
      .WillOnce([](supla_action_hvac_parameters *params) {
        EXPECT_EQ(params->get_mode(), SUPLA_HVAC_MODE_HEAT);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "heat");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, cool) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_parameters(NotNull()))
      .WillOnce([](supla_action_hvac_parameters *params) {
        EXPECT_EQ(params->get_mode(), SUPLA_HVAC_MODE_COOL);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "cool");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

TEST_F(MqttSubscriberTest, heatCool) {
  waitForConnection();
  waitForData(3);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_temperature).Times(0);

  EXPECT_CALL(*getValueSetter(), action_hvac_set_parameters(NotNull()))
      .WillOnce([](supla_action_hvac_parameters *params) {
        EXPECT_EQ(params->get_mode(), SUPLA_HVAC_MODE_HEAT_COOL);
      });

  getLibAdapter()->on_message_received(
      "supla/7720767494dd87196e1896c7cbab707c/devices/10/channels/1234/"
      "execute_action",
      "heat_cool");

  ASSERT_EQ(getValueSetter()->counterSetCount(), 0);
}

} /* namespace testing */
