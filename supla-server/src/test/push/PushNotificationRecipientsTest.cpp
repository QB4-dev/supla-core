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

#include "PushNotificationRecipientsTest.h"

namespace testing {

PushNotificationRecipientsTest::PushNotificationRecipientsTest(void) {}

PushNotificationRecipientsTest::~PushNotificationRecipientsTest(void) {}

TEST_F(PushNotificationRecipientsTest, counting) {
  EXPECT_EQ(recipients.total_count(), 0);
  EXPECT_EQ(recipients.count(platform_unknown), 0);
  EXPECT_EQ(recipients.count(platform_push_android), 0);
  EXPECT_EQ(recipients.count(platform_push_ios), 0);

  recipients.add(new supla_pn_recipient(1, 0, false, "id1", "", 0),
                 platform_push_android);

  EXPECT_EQ(recipients.total_count(), 1);
  EXPECT_EQ(recipients.count(platform_unknown), 0);
  EXPECT_EQ(recipients.count(platform_push_android), 1);
  EXPECT_EQ(recipients.count(platform_push_ios), 0);

  recipients.add(new supla_pn_recipient(2, 1, false, "id2", "", 0),
                 platform_push_android);

  EXPECT_EQ(recipients.total_count(), 2);
  EXPECT_EQ(recipients.count(platform_unknown), 0);
  EXPECT_EQ(recipients.count(platform_push_android), 2);
  EXPECT_EQ(recipients.count(platform_push_ios), 0);

  recipients.add(new supla_pn_recipient(3, 2, false, "id1", "", 0),
                 platform_push_ios);

  EXPECT_EQ(recipients.total_count(), 3);
  EXPECT_EQ(recipients.count(platform_unknown), 0);
  EXPECT_EQ(recipients.count(platform_push_android), 2);
  EXPECT_EQ(recipients.count(platform_push_ios), 1);

  recipients.add(new supla_pn_recipient(3, 0, false, "id1", "", 0),
                 platform_push_ios);

  EXPECT_EQ(recipients.total_count(), 4);
  EXPECT_EQ(recipients.count(platform_unknown), 0);
  EXPECT_EQ(recipients.count(platform_push_android), 2);
  EXPECT_EQ(recipients.count(platform_push_ios), 2);
}

TEST_F(PushNotificationRecipientsTest, addAndGet) {
  recipients.add(new supla_pn_recipient(1, 0, false, "and1", "", 20),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(2, 0, true, "ios1", "", 21),
                 platform_push_ios);
  recipients.add(new supla_pn_recipient(3, 5, false, "ios2", "", 22),
                 platform_push_ios);

  supla_pn_recipient *r = recipients.get(platform_push_android, 1);
  EXPECT_TRUE(r == nullptr);

  r = recipients.get(platform_push_android, 0);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "and1");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 0);
  EXPECT_EQ(r->get_protocol_version(), 20);
  EXPECT_FALSE(r->is_development_env());

  r = recipients.get(platform_push_ios, 0);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "ios1");
  EXPECT_EQ(r->get_client_id(), 2);
  EXPECT_EQ(r->get_app_id(), 0);
  EXPECT_EQ(r->get_protocol_version(), 21);
  EXPECT_TRUE(r->is_development_env());

  r = recipients.get(platform_push_ios, 1);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "ios2");
  EXPECT_EQ(r->get_client_id(), 3);
  EXPECT_EQ(r->get_app_id(), 5);
  EXPECT_EQ(r->get_protocol_version(), 22);
  EXPECT_FALSE(r->is_development_env());

  r = recipients.get(platform_push_ios, 2);
  EXPECT_TRUE(r == nullptr);

  // The order of rising from the platform on the map

  r = recipients.get(0);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "ios1");
  EXPECT_EQ(r->get_client_id(), 2);
  EXPECT_EQ(r->get_app_id(), 0);
  EXPECT_TRUE(r->is_development_env());

  r = recipients.get(1);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "ios2");
  EXPECT_EQ(r->get_client_id(), 3);
  EXPECT_EQ(r->get_app_id(), 5);
  EXPECT_FALSE(r->is_development_env());

  r = recipients.get(2);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "and1");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 0);
  EXPECT_FALSE(r->is_development_env());

  r = recipients.get(3);
  EXPECT_TRUE(r == nullptr);
}

TEST_F(PushNotificationRecipientsTest, clear) {
  recipients.add(new supla_pn_recipient(1, 0, false, "and1", "", 0),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(2, 0, true, "ios1", "", 0),
                 platform_push_ios);
  recipients.clear();
  EXPECT_EQ(recipients.total_count(), 0);
}

TEST_F(PushNotificationRecipientsTest, ignoringDuplicates) {
  recipients.add(new supla_pn_recipient(1, 0, false, "t1", "", 0),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(1, 0, false, "t2", "", 0),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(1, 0, false, "t1", "", 0),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(1, 1, false, "t1", "", 0),
                 platform_push_android);
  recipients.add(new supla_pn_recipient(1, 0, true, "t1", "", 0),
                 platform_push_ios);

  supla_pn_recipient *r = recipients.get(platform_push_android, 0);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "t1");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 0);

  r = recipients.get(platform_push_android, 1);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "t2");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 0);

  r = recipients.get(platform_push_android, 2);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "t1");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 1);

  r = recipients.get(platform_push_ios, 0);
  ASSERT_TRUE(r != nullptr);
  EXPECT_EQ(r->get_token(), "t1");
  EXPECT_EQ(r->get_client_id(), 1);
  EXPECT_EQ(r->get_app_id(), 0);
}

TEST_F(PushNotificationRecipientsTest, profileName) {
  supla_pn_recipient r0(1, 0, false, "and1", "", 0);
  EXPECT_EQ(r0.get_profile_name(), "");
  supla_pn_recipient r1(1, 0, false, "and1", "MyProfile", 0);
  EXPECT_EQ(r1.get_profile_name(), "MyProfile");
  supla_pn_recipient r2(1, 0, false, "and1", "XYZ", 0);
  EXPECT_EQ(r2.get_profile_name(), "XYZ");
}
} /* namespace testing */
