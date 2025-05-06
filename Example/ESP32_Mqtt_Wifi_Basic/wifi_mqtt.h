// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H

#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>

extern MQTTClient mqttClient;

void setWifi();
void setMqtt();
void messageReceived(String &topic, String &payload);
#endif // WIFI_MQTT_H