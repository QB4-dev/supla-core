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

#ifndef REMOTE_GATEWAY_ACCESS_TOKEN_H_
#define REMOTE_GATEWAY_ACCESS_TOKEN_H_

#include <map>
#include <string>

enum _platform_e {
  platform_unknown = 0,
  platform_push_ios = 1,
  platform_push_android = 2,
  platform_homegraph = 3
};

class supla_remote_gateway_access_token {
 private:
  struct timeval expires_at;
  std::string production_url;
  std::string development_url;
  std::string token;
  int app_id;
  _platform_e platform;
  std::map<std::string, std::string> extra_fields;

 public:
  supla_remote_gateway_access_token(void);
  supla_remote_gateway_access_token(const std::string &production_url,
                                    const std::string &development_url,
                                    const std::string &token, int expires_in,
                                    _platform_e platform, int app_id);
  virtual ~supla_remote_gateway_access_token(void);

  _platform_e get_platform(void);
  int get_app_id(void);
  std::string get_url(bool development_env);
  std::string get_token(void);
  int get_expires_in(void);
  void set_token(const std::string &token);
  bool is_valid(void);
  void get_expiration_time_if_earlier(struct timeval *expires_at);
  void set_extra_field(std::string name, std::string value);
  std::string get_extra_field(std::string name);
};

#endif /* REMOTE_GATEWAY_ACCESS_TOKEN_H_ */
