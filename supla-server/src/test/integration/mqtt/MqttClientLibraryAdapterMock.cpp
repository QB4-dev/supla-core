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

#include "MqttClientLibraryAdapterMock.h"
#include <string.h>
#include <unistd.h>
#include "lck.h"
#include "log.h"

MqttClientLibraryAdapterMock::MqttClientLibraryAdapterMock(
    supla_mqtt_client_settings *settings)
    : supla_mqtt_client_library_adapter(settings) {
  this->lck = lck_init();
  this->connected = false;
}

MqttClientLibraryAdapterMock::~MqttClientLibraryAdapterMock(void) {
  clear();
  lck_free(lck);
}

void MqttClientLibraryAdapterMock::client_connect(
    supla_mqtt_client *supla_client_instance) {
  lck_lock(lck);
  connected = true;
  lck_unlock(lck);

  if (on_connected_callback) {
    on_connected_callback(supla_client_instance);
  }
}

bool MqttClientLibraryAdapterMock::is_connected(void) {
  bool result = false;

  lck_lock(lck);
  result = connected;
  lck_unlock(lck);

  return result;
}

void MqttClientLibraryAdapterMock::iterate(void) { usleep(100); }

void MqttClientLibraryAdapterMock::disconnect(void) {
  lck_lock(lck);
  connected = false;
  lck_unlock(lck);
}

void MqttClientLibraryAdapterMock::cleanup(void) {}

void MqttClientLibraryAdapterMock::raise_event(void) {}

bool MqttClientLibraryAdapterMock::subscribe(const char *topic_name,
                                             QOS_Level max_qos_level) {
  return true;
}

bool MqttClientLibraryAdapterMock::publish(const char *topic_name,
                                           const void *message,
                                           size_t message_size,
                                           QOS_Level qos_level, bool retain) {
  _mqtt_test_message_t m;
  memset(&m, 0, sizeof(_mqtt_test_message_t));

  m.topic_name = strdup(topic_name);
  if (message && message_size) {
    m.message = malloc(message_size + 1);
    if (m.message) {
      memcpy(m.message, message, message_size);
      ((char *)m.message)[message_size] = 0;
      m.message_size = message_size;
    }
  }

  messages.push_back(m);
  return true;
}

void MqttClientLibraryAdapterMock::clear(void) {
  lck_lock(lck);
  while (messages.size()) {
    _mqtt_test_message_t m = messages.front();
    if (m.topic_name != NULL) {
      free(m.topic_name);
    }
    if (m.message) {
      free(m.message);
    }
    messages.pop_front();
  }
  lck_unlock(lck);
}

int MqttClientLibraryAdapterMock::count(void) {
  int result = 0;
  lck_lock(lck);
  result = messages.size();
  lck_unlock(lck);
  return result;
}

_mqtt_test_message_t MqttClientLibraryAdapterMock::pop(void) {
  _mqtt_test_message_t result;
  lck_lock(lck);
  result = messages.front();
  messages.pop_front();
  lck_unlock(lck);
  return result;
}
