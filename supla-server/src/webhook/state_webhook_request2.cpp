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

#include "webhook/state_webhook_request2.h"

#include "webhook/state_webhook_client2.h"

using std::shared_ptr;

supla_state_webhook_request2::supla_state_webhook_request2(
    const supla_caller &caller, int user_id, int device_id, int channel_id,
    event_type et, int actions, supla_asynctask_queue *queue,
    supla_abstract_asynctask_thread_pool *pool,
    supla_abstract_channel_property_getter *property_getter,
    supla_abstract_state_webhook_credentials *credentials)
    : supla_asynctask_http_request(caller, user_id, device_id, channel_id, et,
                                   queue, pool, property_getter) {
  this->actions = actions;
  this->credentials = credentials;
}

supla_state_webhook_request2::~supla_state_webhook_request2(void) {}

bool supla_state_webhook_request2::make_request(
    supla_abstract_curl_adapter *curl_adapter) {
  if (!credentials->is_access_token_exists()) {
    return false;
  }

  supla_state_webhook_client2 client(get_channel_id(), curl_adapter,
                                     credentials);

  if (get_event_type() == ET_ACTION_TRIGGERED) {
    return client.triggered_actions_report(actions);
  }

  int func = 0;
  bool online = false;
  supla_channel_value *value = get_channel_value(&func, &online);

  if (!value) {
    return false;
  }

  client.set_channel_connected(online);
  client.set_channel_value(value);

  bool result = false;

  switch (func) {
    case SUPLA_CHANNELFNC_POWERSWITCH:
      return client.power_switch_report();

    case SUPLA_CHANNELFNC_LIGHTSWITCH:
      return client.light_switch_report();
      break;

    case SUPLA_CHANNELFNC_STAIRCASETIMER:
      return client.staircase_timer_report();
      break;

    case SUPLA_CHANNELFNC_THERMOMETER:
      result = client.temperature_report();
      break;

    case SUPLA_CHANNELFNC_HUMIDITY:
      result = client.humidity_report();
      break;

    case SUPLA_CHANNELFNC_HUMIDITYANDTEMPERATURE:
      result = client.temperature_and_humidity_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_GATEWAY:
      result = client.gateway_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_GATE:
      result = client.gate_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_GARAGEDOOR:
      result = client.garage_door_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_NOLIQUIDSENSOR:
      result = client.noliquid_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_DOOR:
      result = client.door_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_ROLLERSHUTTER:
      result = client.roller_shutter_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_ROOFWINDOW:
      result = client.roof_window_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_OPENINGSENSOR_WINDOW:
      result = client.window_opening_sensor_report();
      break;

    case SUPLA_CHANNELFNC_MAILSENSOR:
      result = client.mail_sensor_report();
      break;

    case SUPLA_CHANNELFNC_CONTROLLINGTHEROLLERSHUTTER:
      result = client.roller_shutter_report();
      break;

    case SUPLA_CHANNELFNC_CONTROLLINGTHEROOFWINDOW:
      result = client.roof_window_report();
      break;

    case SUPLA_CHANNELFNC_WINDSENSOR:
      result = client.wind_sensor_report();
      break;

    case SUPLA_CHANNELFNC_PRESSURESENSOR:
      result = client.pressure_sensor_report();
      break;

    case SUPLA_CHANNELFNC_RAINSENSOR:
      result = client.rain_sensor_report();
      break;

    case SUPLA_CHANNELFNC_WEIGHTSENSOR:
      result = client.weight_sensor_report();
      break;

    case SUPLA_CHANNELFNC_DISTANCESENSOR:
      result = client.distance_sensor_report();
      break;

    case SUPLA_CHANNELFNC_DEPTHSENSOR:
      result = client.depth_sensor_report();
      break;

    case SUPLA_CHANNELFNC_DIMMER:
      result = client.dimmer_report();
      break;

    case SUPLA_CHANNELFNC_DIMMERANDRGBLIGHTING:
      result = client.dimmer_and_rgb_report();
      break;

    case SUPLA_CHANNELFNC_RGBLIGHTING:
      result = client.rgb_report();
      break;

    case SUPLA_CHANNELFNC_ELECTRICITY_METER:
      if (get_property_getter()) {
        supla_channel_electricity_measurement *em =
            get_property_getter()->get_electricity_measurement();
        if (em) {
          result = client.electricity_measurement_report(em);
          delete em;
        }
      }
      break;

    case SUPLA_CHANNELFNC_IC_ELECTRICITY_METER:
    case SUPLA_CHANNELFNC_IC_GAS_METER:
    case SUPLA_CHANNELFNC_IC_WATER_METER:
    case SUPLA_CHANNELFNC_IC_HEAT_METER:

      if (get_property_getter()) {
        supla_channel_ic_measurement *icm =
            get_property_getter()->get_ic_measurement();

        if (icm != nullptr) {
          switch (func) {
            case SUPLA_CHANNELFNC_IC_ELECTRICITY_METER:
              result =
                  client.impulse_counter_electricity_measurement_report(icm);
              break;
            case SUPLA_CHANNELFNC_IC_GAS_METER:
              result = client.impulse_counter_gas_measurement_report(icm);
              break;
            case SUPLA_CHANNELFNC_IC_WATER_METER:
              result = client.impulse_counter_water_measurement_report(icm);
              break;
            case SUPLA_CHANNELFNC_IC_HEAT_METER:
              result = client.impulse_counter_heat_measurement_report(icm);
              break;
          }

          delete icm;
        }
      }

      break;
  }

  delete value;

  return result;
}

/*
bool supla_state_webhook_request::isCancelled(void *sthread) {
  if (sthread_isterminated(sthread)) {
    return true;
  }

  return !getUser()->stateWebhookCredentials()->isAccessTokenExists();
}



bool supla_state_webhook_request::verifyExisting(supla_http_request *existing) {
  if (existing->getEventType() == getEventType()) {
    unsigned int actions = getActions();

    existing->accessExtraParams(
        [actions](supla_http_request_extra_params *_params) -> void {
          supla_http_request_action_trigger_extra_params *params =
              dynamic_cast<supla_http_request_action_trigger_extra_params *>(
                  _params);
          if (params) {
            params->addActions(actions);
          }
        });

    duplicateExists = true;
  }
  return true;
}


bool supla_state_webhook_request::isCallerAccepted(const supla_caller &caller,
                                                   bool verification) {
  supla_state_webhook_credentials *credentials =
      getUser()->stateWebhookCredentials();
  if (credentials == NULL || !credentials->isAccessTokenExists() ||
      !credentials->isUrlValid()) {
    return false;
  }

  switch (caller.get_type()) {
    case ctDevice:
    case ctClient:
    case ctAmazonAlexa:
    case ctGoogleHome:
    case ctActionTrigger:
    case ctScene:
    case ctIPC:
    case ctCyclicTask:
    case ctMQTT: {
      channel_complex_value value =
          getUser()->get_channel_complex_value(getChannelId());

      list<int> fids = credentials->getFunctionsIds();
      for (int f : fids) {
        if (f == value.function) {
          switch (value.function) {
            case SUPLA_CHANNELFNC_DIMMER:
            case SUPLA_CHANNELFNC_DIMMERANDRGBLIGHTING:
            case SUPLA_CHANNELFNC_RGBLIGHTING:
              delayTime = 2500000;
              return true;
            case SUPLA_CHANNELFNC_THERMOMETER:
            case SUPLA_CHANNELFNC_HUMIDITY:
            case SUPLA_CHANNELFNC_HUMIDITYANDTEMPERATURE:
            case SUPLA_CHANNELFNC_WINDSENSOR:
            case SUPLA_CHANNELFNC_PRESSURESENSOR:
            case SUPLA_CHANNELFNC_RAINSENSOR:
            case SUPLA_CHANNELFNC_WEIGHTSENSOR:
            case SUPLA_CHANNELFNC_DISTANCESENSOR:
            case SUPLA_CHANNELFNC_DEPTHSENSOR:
            case SUPLA_CHANNELFNC_ELECTRICITY_METER:
            case SUPLA_CHANNELFNC_IC_ELECTRICITY_METER:
            case SUPLA_CHANNELFNC_IC_GAS_METER:
            case SUPLA_CHANNELFNC_IC_WATER_METER:
            case SUPLA_CHANNELFNC_IC_HEAT_METER:
              delayTime = 15000000;
              return true;
            case SUPLA_CHANNELFNC_POWERSWITCH:
            case SUPLA_CHANNELFNC_LIGHTSWITCH:
            case SUPLA_CHANNELFNC_STAIRCASETIMER:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_GATEWAY:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_GATE:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_GARAGEDOOR:
            case SUPLA_CHANNELFNC_NOLIQUIDSENSOR:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_DOOR:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_ROLLERSHUTTER:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_ROOFWINDOW:
            case SUPLA_CHANNELFNC_OPENINGSENSOR_WINDOW:
            case SUPLA_CHANNELFNC_MAILSENSOR:
            case SUPLA_CHANNELFNC_CONTROLLINGTHEROLLERSHUTTER:
            case SUPLA_CHANNELFNC_CONTROLLINGTHEROOFWINDOW:
              return true;
            case SUPLA_CHANNELFNC_ACTIONTRIGGER:
              delayTime = 100000;
              return true;
            default:
              return false;
          }
        }
      }

      return false;
    } break;
    case ctUnknown:
      return false;
  }

  return false;
}

bool supla_state_webhook_request::isEventTypeAccepted(event_type eventType,
                                                      bool verification) {
  return eventType == ET_CHANNEL_VALUE_CHANGED ||
         eventType == ET_ACTION_TRIGGERED;
}

supla_state_webhook_client *supla_state_webhook_request::getClient(void) {
  supla_state_webhook_credentials *credentials =
      getUser()->stateWebhookCredentials();
  assert(credentials != NULL);

  supla_state_webhook_client *result = NULL;
  lck_lock(lck);
  if (!client) {
    client = new supla_state_webhook_client(
        credentials, credentials->getScheme() == schemeHttps);
  }
  result = client;
  lck_unlock(lck);

  return result;
}



void supla_state_webhook_request::execute(void *sthread) {
  if (getEventType() == ET_ACTION_TRIGGERED) {
    getClient()->triggeredActionsReport(getChannelId(), getActions());
    return;
  }

  channel_complex_value value =
      getUser()->get_channel_complex_value(getChannelId());

  switch (value.function) {
    case SUPLA_CHANNELFNC_POWERSWITCH:
      getClient()->sendPowerSwitchReport(getChannelId(), value.hi,
                                         value.online);
      break;
    case SUPLA_CHANNELFNC_LIGHTSWITCH:
      getClient()->sendLightSwitchReport(getChannelId(), value.hi,
                                         value.online);
      break;
    case SUPLA_CHANNELFNC_STAIRCASETIMER:
      getClient()->sendStaircaseTimerReport(getChannelId(), value.hi,
                                            value.online);
      break;
    case SUPLA_CHANNELFNC_THERMOMETER:
      getClient()->sendTemperatureReport(getChannelId(), value.temperature,
                                         value.online);
      break;
    case SUPLA_CHANNELFNC_HUMIDITY:
      getClient()->sendHumidityReport(getChannelId(), value.humidity,
                                      value.online);
      break;
    case SUPLA_CHANNELFNC_HUMIDITYANDTEMPERATURE:
      getClient()->sendTemperatureAndHumidityReport(
          getChannelId(), value.temperature, value.humidity, value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_GATEWAY:
      getClient()->sendGatewayOpeningSensorReport(getChannelId(), value.hi,
                                                  value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_GATE:
      getClient()->sendGateOpeningSensorReport(getChannelId(), value.hi,
                                               value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_GARAGEDOOR:
      getClient()->sendGarageDoorOpeningSensorReport(getChannelId(), value.hi,
                                                     value.online);
      break;
    case SUPLA_CHANNELFNC_NOLIQUIDSENSOR:
      getClient()->sendNoLiquidSensorReport(getChannelId(), value.hi,
                                            value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_DOOR:
      getClient()->sendDoorOpeningSensorReport(getChannelId(), value.hi,
                                               value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_ROLLERSHUTTER:
      getClient()->sendRollerShutterOpeningSensorReport(getChannelId(),
                                                        value.hi, value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_ROOFWINDOW:
      getClient()->sendRoofWindowOpeningSensorReport(getChannelId(), value.hi,
                                                     value.online);
      break;
    case SUPLA_CHANNELFNC_OPENINGSENSOR_WINDOW:
      getClient()->sendWindowOpeningSensorReport(getChannelId(), value.hi,
                                                 value.online);
      break;
    case SUPLA_CHANNELFNC_MAILSENSOR:
      getClient()->sendMailSensorReport(getChannelId(), value.hi, value.online);
      break;
    case SUPLA_CHANNELFNC_CONTROLLINGTHEROLLERSHUTTER:
      getClient()->sendRollerShutterReport(getChannelId(), value.shut,
                                           value.online);
      break;
    case SUPLA_CHANNELFNC_CONTROLLINGTHEROOFWINDOW:
      getClient()->sendRoofWindowReport(getChannelId(), value.shut,
                                        value.online);
      break;
    case SUPLA_CHANNELFNC_WINDSENSOR:
      getClient()->sendWindSensorReport(getChannelId(), value.wind,
                                        value.online);
      break;
    case SUPLA_CHANNELFNC_PRESSURESENSOR:
      getClient()->sendPressureSensorReport(getChannelId(), value.pressure,
                                            value.online);
      break;
    case SUPLA_CHANNELFNC_RAINSENSOR:
      getClient()->sendRainSensorReport(getChannelId(), value.rain,
                                        value.online);
      break;
    case SUPLA_CHANNELFNC_WEIGHTSENSOR:
      getClient()->sendWeightSensorReport(getChannelId(), value.weight,
                                          value.online);
      break;
    case SUPLA_CHANNELFNC_DISTANCESENSOR:
      getClient()->sendDistanceSensorReport(getChannelId(), value.distance,
                                            value.online);
      break;
    case SUPLA_CHANNELFNC_DEPTHSENSOR:
      getClient()->sendDepthSensorReport(getChannelId(), value.depth,
                                         value.online);
      break;
    case SUPLA_CHANNELFNC_DIMMER:

      getClient()->sendDimmerReport(getChannelId(), value.brightness,
                                    value.on_off, value.online);

      break;
    case SUPLA_CHANNELFNC_DIMMERANDRGBLIGHTING:
      getClient()->sendDimmerAndRgbReport(
          getChannelId(), value.color, value.color_brightness, value.brightness,
          value.on_off, value.online);
      break;
    case SUPLA_CHANNELFNC_RGBLIGHTING:
      getClient()->sendRgbReport(getChannelId(), value.color,
                                 value.color_brightness, value.on_off,
                                 value.online);
      break;
  }

  switch (value.channel_type) {
    case SUPLA_CHANNELTYPE_ELECTRICITY_METER:
      electricityMeterChannelType(&value);
      break;
    case SUPLA_CHANNELTYPE_IMPULSE_COUNTER:
      impulseCounterChannelType(&value);
      break;
  }
}




REGISTER_HTTP_REQUEST_CLASS(supla_state_webhook_request);
*/
