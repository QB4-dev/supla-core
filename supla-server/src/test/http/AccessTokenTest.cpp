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

#include "AccessTokenTest.h"

#include <sys/time.h>

#include "http/remote_gateway_access_token.h"

namespace testing {

AccessTokenTest::AccessTokenTest(void) {}

AccessTokenTest::~AccessTokenTest(void) {}

TEST_F(AccessTokenTest, defaults) {
  supla_remote_gateway_access_token token;
  EXPECT_EQ(token.get_platform(), platform_unknown);
  EXPECT_EQ(token.get_app_id(), 0);
  EXPECT_TRUE(token.get_url(false).empty());
  EXPECT_TRUE(token.get_url(true).empty());
  EXPECT_TRUE(token.get_token().empty());
  EXPECT_GE(token.get_expires_in(), 60 * 60 * 24 * 365 * 10 - 1);
  EXPECT_FALSE(token.is_valid());
}

TEST_F(AccessTokenTest, constructorWithArguments) {
  supla_remote_gateway_access_token token(
      "https://api.push.apple.com", "https://api.development.push.apple.com",
      "6465eece984600c0a81e3d6a3a93190c2d0be", 60, platform_push_ios, 1);

  EXPECT_EQ(token.get_platform(), platform_push_ios);
  EXPECT_EQ(token.get_app_id(), 1);
  EXPECT_EQ(token.get_url(false), "https://api.push.apple.com");
  EXPECT_EQ(token.get_url(true), "https://api.development.push.apple.com");
  EXPECT_EQ(token.get_token(), "6465eece984600c0a81e3d6a3a93190c2d0be");
  EXPECT_GE(token.get_expires_in(), 59);
  EXPECT_LE(token.get_expires_in(), 60);
  EXPECT_TRUE(token.is_valid());
}

TEST_F(AccessTokenTest, missingDevelopmentUrlInConstructor) {
  supla_remote_gateway_access_token token(
      "https://api.push.apple.com", "", "6465eece984600c0a81e3d6a3a93190c2d0be",
      60, platform_push_ios, 1);

  EXPECT_EQ(token.get_url(true), "https://api.push.apple.com");
  EXPECT_EQ(token.get_url(false), "https://api.push.apple.com");
}

TEST_F(AccessTokenTest, validation) {
  supla_remote_gateway_access_token token("a", "b", "c", 2, platform_push_ios,
                                          1);
  EXPECT_TRUE(token.is_valid());
  usleep(2000000);
  EXPECT_FALSE(token.is_valid());
}

TEST_F(AccessTokenTest, getExpirationTimeIfEarlier) {
  supla_remote_gateway_access_token token("a", "b", "c", 60, platform_push_ios,
                                          1);

  struct timeval now1 = {};
  gettimeofday(&now1, nullptr);

  struct timeval now2 = now1;

  token.get_expiration_time_if_earlier(&now1);
  EXPECT_TRUE(now1.tv_sec == now2.tv_sec && now1.tv_usec == now2.tv_usec);

  now1.tv_sec += 65;
  token.get_expiration_time_if_earlier(&now1);

  EXPECT_GE(now1.tv_sec - now2.tv_sec, 59);
  EXPECT_LE(now1.tv_sec - now2.tv_sec, 61);
}

TEST_F(AccessTokenTest, extraFields) {
  supla_remote_gateway_access_token token("a", "b", "c", 60, platform_push_ios,
                                          1);
  EXPECT_EQ(token.get_extra_field("extra1"), "");
  EXPECT_EQ(token.get_extra_field("extra2"), "");
  EXPECT_EQ(token.get_extra_field("extra3"), "");

  token.set_extra_field("extra1", "e1");
  EXPECT_EQ(token.get_extra_field("extra1"), "e1");

  token.set_extra_field("extra1", "e2");
  token.set_extra_field("extra2", "123-2");
  token.set_extra_field("extra3", "3-345");

  EXPECT_EQ(token.get_extra_field("extra1"), "e2");
  EXPECT_EQ(token.get_extra_field("extra2"), "123-2");
  EXPECT_EQ(token.get_extra_field("extra3"), "3-345");
}

} /* namespace testing */
