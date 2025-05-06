#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H

#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>

// Wi-Fi 및 MQTT 클라이언트 객체
extern MQTTClient client;

// 함수 선언
void setWifi();
void setMqtt();
void messageReceived(String &topic, String &payload);
void sendWeightMQTT(float weightValue);
#endif // WIFI_MQTT_H
