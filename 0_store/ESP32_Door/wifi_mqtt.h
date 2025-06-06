// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H

#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>
extern WiFiClient net;
extern MQTTClient mqttClient;

void setWifi();
void setMqtt();
void messageReceived(String &topicName, String &payload);
#endif // WIFI_MQTT_H