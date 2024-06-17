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

#include "voice_assistant_sync_thread_pool.h"

#include <string>

#include "asynctask/asynctask_queue.h"

using std::string;

// Separate pool for voice assistant as http sync requests take a few seconds.

supla_voice_assistant_sync_thread_pool
    *supla_voice_assistant_sync_thread_pool::_global_instance = NULL;

supla_voice_assistant_sync_thread_pool::supla_voice_assistant_sync_thread_pool(
    supla_asynctask_queue *queue)
    : supla_asynctask_http_thread_pool(queue) {}

supla_voice_assistant_sync_thread_pool::~supla_voice_assistant_sync_thread_pool(
    void) {}

unsigned int supla_voice_assistant_sync_thread_pool::thread_count_limit(void) {
  return 10;
}

int supla_voice_assistant_sync_thread_pool::tasks_per_thread(void) { return 1; }

bool supla_voice_assistant_sync_thread_pool::should_keep_alive(
    unsigned long long usec_since_last_exec, size_t thread_count) {
  return false;
}

string supla_voice_assistant_sync_thread_pool::pool_name(void) {
  return "VoiceAssistantSyncPool";
}

// static
supla_voice_assistant_sync_thread_pool *
supla_voice_assistant_sync_thread_pool::global_instance(void) {
  if (_global_instance == nullptr) {
    _global_instance = new supla_voice_assistant_sync_thread_pool(
        supla_asynctask_queue::global_instance());
  }

  return _global_instance;
}
