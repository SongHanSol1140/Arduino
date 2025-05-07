// wifi_mqtt.h
#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <MQTT.h>

extern WiFiClient net;
extern MQTTClient mqttClient;
extern ESP8266WebServer server;

void setWifi();
void setMqtt();
void messageReceived(String &topic, String &payload);
void publishMessage(const String &message);
#endif // WIFI_MQTT_H