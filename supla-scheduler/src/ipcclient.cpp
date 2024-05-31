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

#include "ipcclient.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "log.h"
#include "schedulercfg.h"

const char hello[] = "SUPLA SERVER CTRL\n";

const char cmd_is_iodev_connected[] = "IS-IODEV-CONNECTED";

const char cmd_get_double_value[] = "GET-DOUBLE-VALUE";
const char cmd_get_char_value[] = "GET-CHAR-VALUE";
const char cmd_get_rgbw_value[] = "GET-RGBW-VALUE";
const char cmd_get_valve_value[] = "GET-VALVE-VALUE";
const char cmd_get_digiglass_value[] = "GET-DIGIGLASS-VALUE";
const char cmd_get_fb_value[] = "GET-FACADE-BLIND-VALUE";

const char cmd_set_char_value[] = "SET-CHAR-VALUE";
const char cmd_set_rgbw_value[] = "SET-RGBW-VALUE";

const char cmd_set_cg_char_value[] = "SET-CG-CHAR-VALUE";
const char cmd_set_cg_rgbw_value[] = "SET-CG-RGBW-VALUE";
const char cmd_set_digiglass_value[] = "SET-DIGIGLASS-VALUE";
const char cmd_action_shut_partially[] = "ACTION-SHUT-PARTIALLY";
const char cmd_action_cg_shut_partially[] = "ACTION-CG-SHUT-PARTIALLY";

const char cmd_action_copy[] = "ACTION-COPY";
const char cmd_action_cg_copy[] = "ACTION-CG-COPY";

const char cmd_execute_scene[] = "EXECUTE-SCENE";
const char cmd_interrupt_scene[] = "INTERRUPT-SCENE";
const char cmd_interrupt_and_execute_scene[] = "INTERRUPT-AND-EXECUTE-SCENE";

const char ipc_result_value[] = "VALUE:";
const char ipc_result_ok[] = "OK:";
const char ipc_result_is_during_execution[] = "IS-DURING-EXECUTION:";
const char ipc_result_connected[] = "CONNECTED:";
const char ipc_result_disconnected[] = "DISCONNECTED:";

ipc_client::ipc_client() { this->sfd = -1; }

ipc_client::~ipc_client() { ipc_disconnect(); }

int ipc_client::read(void) {
  if (sfd == -1) return 0;

  fd_set set;
  struct timeval timeout;
  FD_ZERO(&set);
  FD_SET(sfd, &set);
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  memset(buffer, 0, IPC_BUFFER_SIZE);

  int rv = select(sfd + 1, &set, NULL, NULL, &timeout);

  if (rv == 0) {
    return 0;
  }

  ssize_t len = recv(sfd, buffer, IPC_BUFFER_SIZE, 0);

  if (len > 0) {
    if (len >= IPC_BUFFER_SIZE) len = IPC_BUFFER_SIZE - 1;

    buffer[len] = 0;
    // supla_log(LOG_DEBUG, "READ %s", buffer);
    return len;
  }

  return 0;
}

bool ipc_client::ipc_connect(void) {
  struct sockaddr_un remote;
  int len;

  if (sfd != -1) return true;

  if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    supla_log(LOG_ERR, "Socket error %i", errno);
    return false;
  }

  remote.sun_family = AF_UNIX;
  snprintf(remote.sun_path, sizeof(remote.sun_path), "%s",
           scfg_string(CFG_IPC_SOCKET_PATH));

  len = strnlen(remote.sun_path, 107) + sizeof(remote.sun_family);
  if (connect(sfd, (struct sockaddr *)&remote, len) == -1) {
    supla_log(LOG_ERR, "IPC connect error %i", errno);

    ipc_disconnect();
    return false;
  }

  if (read() && strcmp(buffer, hello) == 0) return true;

  ipc_disconnect();

  return false;
}

bool ipc_client::ipc_disconnect(void) {
  if (sfd == -1) return false;

  close(sfd);
  sfd = -1;

  return true;
}

bool ipc_client::get_value(const char *cmd, int user_id, int device_id,
                           int channel_id) {
  if (!ipc_connect()) return false;

  snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i\n", cmd, user_id, device_id,
           channel_id);
  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  if (read() &&
      memcmp(buffer, ipc_result_value, strnlen(ipc_result_value, 255)) == 0) {
    return true;
  }

  return false;
}

char ipc_client::is_connected(int user_id, int device_id) {
  if (ipc_connect()) {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i\n", cmd_is_iodev_connected,
             user_id, device_id);
    // supla_log(LOG_DEBUG, "%s", buffer);
    send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

    if (read()) {
      if (memcmp(buffer, ipc_result_connected,
                 strnlen(ipc_result_connected, 255)) == 0)
        return IPC_RESULT_CONNECTED;

      if (memcmp(buffer, ipc_result_disconnected,
                 strnlen(ipc_result_disconnected, 255)) == 0)
        return IPC_RESULT_DISCONNECTED;
    }
  }

  return IPC_RESULT_SERVER_UNREACHABLE;
}

bool ipc_client::get_double_value(int user_id, int device_id, int channel_id,
                                  double *value) {
  if (value == NULL ||
      !get_value(cmd_get_double_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%lf", value) != 1)
    return false;

  return true;
}

bool ipc_client::get_char_value(int user_id, int device_id, int channel_id,
                                char *value) {
  int x = 0;

  if (value == NULL ||
      !get_value(cmd_get_char_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%i", &x) != 1)
    return false;

  if ((unsigned int)x >= 255) return false;

  *value = x;

  return true;
}

bool ipc_client::get_fb_value(int user_id, int device_id, int channel_id,
                              char *position, char *tilt) {
  float angle = 0;
  int _position = 0;
  int _tilt = 0;
  if (position == nullptr || tilt == nullptr ||
      !get_value(cmd_get_fb_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%i,%i,%f", &_position,
             &_tilt, &angle) != 3)
    return false;

  if (_position >= 0 && _position <= 100) {
    *position = _position;
  } else {
    *position = -1;
  }

  if (_tilt >= 0 && _tilt <= 100) {
    *tilt = _tilt;
  } else {
    *tilt = -1;
  }

  return true;
}

bool ipc_client::get_rgbw_value(int user_id, int device_id, int channel_id,
                                int *color, char *color_brightness,
                                char *brightness) {
  int _color_brightness = 0;
  int _brightness = 0;

  if (color == NULL || color_brightness == NULL || brightness == NULL ||
      !get_value(cmd_get_rgbw_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%i,%i,%i", color,
             &_color_brightness, &_brightness) != 3)
    return false;

  if (_color_brightness < 0 || _color_brightness > 100 || _brightness < 0 ||
      _brightness > 100)
    return false;

  *color_brightness = _color_brightness;
  *brightness = _brightness;

  return true;
}

bool ipc_client::get_valve_value(int user_id, int device_id, int channel_id,
                                 TValve_Value *value) {
  if (value == NULL ||
      !get_value(cmd_get_valve_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%hhu,%hhu",
             &value->closed, &value->flags) != 2) {
    memset(value, 0, sizeof(TValve_Value));
    return false;
  }

  return true;
}

bool ipc_client::get_digiglass_value(int user_id, int device_id, int channel_id,
                                     int *mask) {
  if (mask == NULL ||
      !get_value(cmd_get_digiglass_value, user_id, device_id, channel_id) ||
      sscanf(&buffer[strnlen(ipc_result_value, 255)], "%i", mask) != 1) {
    *mask = 0;
    return false;
  }

  return true;
}

bool ipc_client::check_set_result(void) {
  if (read() &&
      memcmp(buffer, ipc_result_ok, strnlen(ipc_result_ok, 255)) == 0) {
    return true;
  }

  return false;
}

bool ipc_client::set_char_value(int user_id, int device_id, int channel_id,
                                int channel_group_id, char value) {
  if (!ipc_connect()) return false;

  if (channel_group_id) {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i\n", cmd_set_cg_char_value,
             user_id, channel_group_id, value);
  } else {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i\n", cmd_set_char_value,
             user_id, device_id, channel_id, value);
  }

  // supla_log(LOG_DEBUG, "IPC %i %s", sfd, buffer);
  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  return check_set_result();
}

bool ipc_client::set_rgbw_value(int user_id, int device_id, int channel_id,
                                int channel_group_id, int color,
                                char color_brightness, char brightness) {
  if (!ipc_connect()) return false;

  if (channel_group_id) {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i,0\n",
             cmd_set_cg_rgbw_value, user_id, channel_group_id, color,
             color_brightness, brightness);
  } else {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i,%i,0\n",
             cmd_set_rgbw_value, user_id, device_id, channel_id, color,
             color_brightness, brightness);
  }

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);
  // supla_log(LOG_DEBUG, "IPC %i %s", sfd, buffer);
  return check_set_result();
}

bool ipc_client::set_digiglass_value(int user_id, int device_id, int channel_id,
                                     int active_bits, int mask) {
  if (!ipc_connect()) return false;

  snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i\n",
           cmd_set_digiglass_value, user_id, device_id, channel_id, active_bits,
           mask);

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);
  // supla_log(LOG_DEBUG, "IPC %i %s", sfd, buffer);
  return check_set_result();
}

bool ipc_client::action_copy(int user_id, int device_id, int channel_id,
                             int channel_group_id, int source_device_id,
                             int source_channel_id) {
  if (!ipc_connect()) return false;

  if (channel_group_id) {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i\n", cmd_action_cg_copy,
             user_id, channel_group_id, source_device_id, source_channel_id);
  } else {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i\n", cmd_action_copy,
             user_id, device_id, channel_id, source_device_id,
             source_channel_id);
  }

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);
  // supla_log(LOG_DEBUG, "IPC %i %s", sfd, buffer);
  return check_set_result();
}

bool ipc_client::action_shut_partially(int user_id, int device_id,
                                       int channel_id, int channel_group_id,
                                       char percentage,
                                       bool percentage_as_delta, char tilt,
                                       bool tilt_as_delta) {
  if (!ipc_connect()) return false;

  if (channel_group_id) {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i,%i\n",
             cmd_action_cg_shut_partially, user_id, channel_group_id,
             percentage, percentage_as_delta, tilt, tilt_as_delta);
  } else {
    snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i,%i,%i,%i,%i,%i\n",
             cmd_action_shut_partially, user_id, device_id, channel_id,
             percentage, percentage_as_delta, tilt, tilt_as_delta);
  }

  // supla_log(LOG_DEBUG, "IPC %i %s", sfd, buffer);
  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  return check_set_result();
}

bool ipc_client::execute_scene(int user_id, int scene_id) {
  if (!ipc_connect()) return false;

  snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i\n", cmd_execute_scene, user_id,
           scene_id);

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  if (read() &&
      (memcmp(buffer, ipc_result_ok, strnlen(ipc_result_ok, 255)) == 0 ||
       memcmp(buffer, ipc_result_is_during_execution,
              strnlen(ipc_result_is_during_execution, 255)) == 0)) {
    return true;
  }

  return false;
}

bool ipc_client::interrupt_scene(int user_id, int scene_id) {
  if (!ipc_connect()) return false;

  snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i\n", cmd_interrupt_scene, user_id,
           scene_id);

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  return check_set_result();
}

bool ipc_client::interrupt_and_execute_scene(int user_id, int scene_id) {
  if (!ipc_connect()) return false;

  snprintf(buffer, IPC_BUFFER_SIZE, "%s:%i,%i\n",
           cmd_interrupt_and_execute_scene, user_id, scene_id);

  send(sfd, buffer, strnlen(buffer, IPC_BUFFER_SIZE - 1), 0);

  return check_set_result();
}
