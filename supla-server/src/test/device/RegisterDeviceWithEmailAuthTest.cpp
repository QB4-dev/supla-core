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

#include <device/RegisterDeviceWithEmailAuthTest.h>

namespace testing {

RegisterDeviceWithEmailAuthTest::RegisterDeviceWithEmailAuthTest()
    : RegisterDeviceTest() {}

RegisterDeviceWithEmailAuthTest::~RegisterDeviceWithEmailAuthTest() {}

TEST_F(RegisterDeviceWithEmailAuthTest, invalidGUID) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_GUID_ERROR, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, invalidAuthkey) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_AUTHKEY_ERROR, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, dbaConnectionFailed) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(false));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(false));
  EXPECT_CALL(dba, disconnect).Times(0);

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_TEMPORARILY_UNAVAILABLE,
                  result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, emailNotFound) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(0));

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_BAD_CREDENTIALS, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, getObjectIdWithFail) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _)).Times(1).WillOnce(Return(false));

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_BAD_CREDENTIALS, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest,
       deviceNotExistsAndRegistrationDisabled) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _))
      .Times(1)
      .WillOnce([](int user_id, const char guid[SUPLA_GUID_SIZE], int *id) {
        *id = 0;
        return true;
      });

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));

  EXPECT_CALL(dba, start_transaction).Times(1);

  EXPECT_CALL(dao, get_device_reg_enabled(25)).Times(1).WillOnce(Return(false));

  EXPECT_CALL(dba, rollback).Times(1);

  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));

  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_REGISTRATION_DISABLED, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, getAuthKeyWithFail) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _))
      .Times(1)
      .WillOnce([](int user_id, const char guid[SUPLA_GUID_SIZE], int *id) {
        *id = 55;
        return true;
      });

  EXPECT_CALL(rd, get_authkey_hash(55, NotNull(), NotNull()))
      .Times(1)
      .WillOnce(
          [](int id, char authkey_hash[BCRYPT_HASH_MAXSIZE], bool *is_null) {
            *is_null = false;
            return false;
          });

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_BAD_CREDENTIALS, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, missingKeyAndRegistrationDisabled) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));

  EXPECT_CALL(dba, start_transaction).Times(1);

  EXPECT_CALL(dao, get_device_reg_enabled(25)).Times(1).WillOnce(Return(false));

  EXPECT_CALL(dba, rollback).Times(1);

  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));

  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _))
      .Times(1)
      .WillOnce([](int user_id, const char guid[SUPLA_GUID_SIZE], int *id) {
        *id = 55;
        return true;
      });

  EXPECT_CALL(rd, get_authkey_hash(55, NotNull(), NotNull()))
      .Times(1)
      .WillOnce(
          [](int id, char authkey_hash[BCRYPT_HASH_MAXSIZE], bool *is_null) {
            *is_null = true;
            return true;
          });

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_REGISTRATION_DISABLED, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, incorrectAuthKey) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _))
      .Times(1)
      .WillOnce([](int user_id, const char guid[SUPLA_GUID_SIZE], int *id) {
        *id = 55;
        return true;
      });

  EXPECT_CALL(rd, get_authkey_hash(55, NotNull(), NotNull()))
      .Times(1)
      .WillOnce(
          [](int id, char authkey_hash[BCRYPT_HASH_MAXSIZE], bool *is_null) {
            *is_null = false;
            snprintf(
                authkey_hash, BCRYPT_HASH_MAXSIZE, "%s",
                "$2a$08$axDwSo52JOLB/hzHvpGAh.JkdmSezHyewYmIp3y3kKHZ3MzNcDyhG");
            return true;
          });

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_BAD_CREDENTIALS, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

TEST_F(RegisterDeviceWithEmailAuthTest, correctAuthKeyAndRegistrtionDisabled) {
  TDS_SuplaRegisterDevice_F register_device_f = {};

  register_device_f.GUID[0] = 1;
  register_device_f.AuthKey[0] = 2;

  snprintf(register_device_f.Email, SUPLA_EMAIL_MAXSIZE, "%s",
           "elon@spacex.com");

  EXPECT_CALL(dba, connect).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, is_connected).Times(1).WillOnce(Return(true));
  EXPECT_CALL(dba, disconnect).Times(1);

  EXPECT_CALL(rd, get_user_id_by_email(StrEq("elon@spacex.com")))
      .Times(1)
      .WillOnce(Return(25));

  EXPECT_CALL(rd, get_object_id(25, _, _))
      .Times(1)
      .WillOnce([](int user_id, const char guid[SUPLA_GUID_SIZE], int *id) {
        *id = 55;
        return true;
      });

  EXPECT_CALL(rd, get_authkey_hash(55, NotNull(), NotNull()))
      .Times(1)
      .WillOnce(
          [](int id, char authkey_hash[BCRYPT_HASH_MAXSIZE], bool *is_null) {
            *is_null = false;
            snprintf(
                authkey_hash, BCRYPT_HASH_MAXSIZE, "%s",
                "$2a$04$oo/qlYbeL.Gvk.1S.ZJL0eUkAgUizZ8.lqNqQXWD93mKfOxznaowO");
            return true;
          });

  EXPECT_CALL(srpcAdapter, sd_async_registerdevice_result(_))
      .Times(1)
      .WillOnce([](TSD_SuplaRegisterDeviceResult *result) {
        EXPECT_EQ(SUPLA_RESULTCODE_REGISTRATION_DISABLED, result->result_code);
        EXPECT_EQ(20, result->activity_timeout);
        EXPECT_EQ(SUPLA_PROTO_VERSION, result->version);
        EXPECT_EQ(SUPLA_PROTO_VERSION_MIN, result->version_min);
        return 0;
      });

  rd.register_device(nullptr, &register_device_f, &srpcAdapter, &dba, &dao, 234,
                     4567, 20);

  EXPECT_GE(usecFromSetUp(), rd.get_hold_time_on_failure_usec());
}

} /* namespace testing */
