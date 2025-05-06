// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H
#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>
extern MQTTClient client;

void setWifi();
void setMqtt();
#endif // WIFI_MQTT_H