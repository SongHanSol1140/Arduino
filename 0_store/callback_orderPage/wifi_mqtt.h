// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H

#include <Arduino.h>     // String 타입을 위해 추가
// #include <ArduinoJson.h> // MQTT에 필요
#include <WiFi.h>


void setWifi();
String urlEncode(const String &str);
void smsSend(const String destNumber, const char *smsMsg);
#endif // WIFI_MQTT_H