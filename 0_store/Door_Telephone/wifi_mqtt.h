// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H
#include <WebServer.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <MQTT.h>

extern WebServer httpServer;
extern MQTTClient client;

void setWifi();
void setMqtt();
void messageReceived(String &topic, String &payload);
void handleCallCancel();
#endif // WIFI_MQTT_H