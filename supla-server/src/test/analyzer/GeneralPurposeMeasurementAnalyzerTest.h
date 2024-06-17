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

#ifndef GENERAL_PURPOSE_MEASUREMENT_ANALYZER_TEST_H_
#define GENERAL_PURPOSE_MEASUREMENT_ANALYZER_TEST_H_

#include "analyzer/general_purpose_measurement_analyzer.h"
#include "gtest/gtest.h"  // NOLINT

namespace testing {

class GeneralPurposeMeasurementAnalyzerTest : public Test {
 public:
  supla_general_purpose_measurement_analyzer analyzer;
};

}  // namespace testing

#endif /* GENERAL_PURPOSE_MEASUREMENT_ANALYZER_TEST_H_ */
