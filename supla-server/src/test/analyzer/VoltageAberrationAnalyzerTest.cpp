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

#include "VoltageAberrationAnalyzerTest.h"

namespace testing {

TEST_F(VoltageAberrationAnalyzerTest, belowCounter) {
  EXPECT_EQ(va.get_below_count(), 0);
  va.set_lower_threshold(1);
  va.add_sample(-1);
  va.add_sample(0);
  va.add_sample(1);
  va.add_sample(2);
  EXPECT_EQ(va.get_below_count(), 1);
  EXPECT_EQ(va.get_sample_count(), 4);

  va.add_sample(-2);
  va.add_sample(-3);
  EXPECT_EQ(va.get_below_count(), 2);
  EXPECT_EQ(va.get_sample_count(), 6);
}

TEST_F(VoltageAberrationAnalyzerTest, aboveCounter) {
  EXPECT_EQ(va.get_above_count(), 0);
  va.set_upper_threshold(5);
  va.add_sample(-1);
  va.add_sample(2);
  va.add_sample(5);
  va.add_sample(10);
  va.add_sample(12);
  EXPECT_EQ(va.get_above_count(), 1);
  EXPECT_EQ(va.get_sample_count(), 5);

  va.add_sample(4);
  va.add_sample(6);
  va.add_sample(7);

  EXPECT_EQ(va.get_above_count(), 2);
  EXPECT_EQ(va.get_sample_count(), 8);
}

TEST_F(VoltageAberrationAnalyzerTest, timeAbove) {
  va.set_upper_threshold(5);
  va.add_sample(6);
  usleep(70000);
  va.add_sample(1);
  usleep(50000);
  va.add_sample(10);
  usleep(50000);
  va.add_sample(1);
  usleep(50000);
  va.add_sample(10);
  usleep(50000);

  EXPECT_GE(va.get_max_msec_above(), 70);
  EXPECT_LT(va.get_max_msec_above(), 80);

  EXPECT_GE(va.get_total_msec_above(), 170);
  EXPECT_LT(va.get_total_msec_above(), 180);

  EXPECT_GE(va.get_total_time_msec(), 270);
  EXPECT_LT(va.get_total_time_msec(), 290);
}

TEST_F(VoltageAberrationAnalyzerTest, timeBelow) {
  va.set_lower_threshold(5);
  va.add_sample(4);
  usleep(70000);
  va.add_sample(6);
  usleep(50000);
  va.add_sample(2);
  usleep(50000);
  va.add_sample(10);
  usleep(50000);
  va.add_sample(1);
  usleep(50000);

  EXPECT_GE(va.get_max_msec_below(), 70);
  EXPECT_LT(va.get_max_msec_below(), 80);

  EXPECT_GE(va.get_total_msec_below(), 170);
  EXPECT_LT(va.get_total_msec_below(), 180);

  EXPECT_GE(va.get_total_time_msec(), 270);
  EXPECT_LT(va.get_total_time_msec(), 290);
}

TEST_F(VoltageAberrationAnalyzerTest, reset) {
  va.set_lower_threshold(5);
  va.set_upper_threshold(5);
  va.add_sample(4);
  usleep(50000);
  va.add_sample(6);
  usleep(50000);
  EXPECT_GT(va.get_below_count(), 0);
  EXPECT_GT(va.get_above_count(), 0);
  EXPECT_GT(va.get_max_msec_above(), 0);
  EXPECT_GT(va.get_max_msec_below(), 0);
  EXPECT_GT(va.get_total_msec_above(), 0);
  EXPECT_GT(va.get_total_msec_below(), 0);
  va.reset();
  EXPECT_EQ(va.get_below_count(), 0);
  EXPECT_EQ(va.get_above_count(), 0);
  EXPECT_EQ(va.get_max_msec_above(), 0);
  EXPECT_EQ(va.get_max_msec_below(), 0);
  EXPECT_EQ(va.get_total_msec_above(), 0);
  EXPECT_EQ(va.get_total_msec_below(), 0);
}

}  // namespace testing
