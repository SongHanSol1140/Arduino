// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H
#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>
extern MQTTClient client;

void setWifi();
void setMqtt();
void Split();
void messageReceived(String &topic, String &payload);
void initMachineValue();
#endif // WIFI_MQTT_H
