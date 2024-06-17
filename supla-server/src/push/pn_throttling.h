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
#ifndef PUSH_NOTIFICATION_THROTTLING_H_
#define PUSH_NOTIFICATION_THROTTLING_H_

#include <list>

#include "http/http_throttling.h"

class supla_pn_throttling {
 private:
  static supla_pn_throttling instance;
  unsigned int time_window_sec;

  typedef struct {
    int user_id;
    struct timeval first_time;
    unsigned int limit;
    unsigned int counter;
  } item_t;

  std::list<item_t> items;
  void *lck;

 protected:
  void set_time_window_sec(unsigned int time_window_sec);

 public:
  supla_pn_throttling(void);
  virtual ~supla_pn_throttling(void);
  unsigned int get_time_window_sec(void);

  virtual bool is_delivery_possible(int user_id, bool *first_time_exceeded,
                                    unsigned int *limit);
  size_t get_user_count(void);
  unsigned int get_count(int user_id);
  unsigned int get_limit(int user_id, long *left);

  static supla_pn_throttling *get_instance(void);
};

#endif /* PUSH_NOTIFICATION_THROTTLING_H_ */
