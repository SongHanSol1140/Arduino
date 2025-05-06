// wifiSetup.h
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "mqttSetup.h"

// 접속할 와이파이 / 비밀번호
const char* ssid = "NNX2-2.4G";
const char *password = "$@43skshslrtm";

IPAddress ip(192, 168, 0, 89);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

int serverPort =  80;
ESP8266WebServer server(serverPort);

void setWifi();
void reconnectWifi();

void setWifi(){
  Serial.println("ESP32 WEB Start");
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("접속시도중");
    delay(1000);
  }
  Serial.print("Wifi IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(serverPort);
  Serial.println("HTTP server started");
  delay(100); 
};

// 와이파이 재접속 함수
void reconnectWifi(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Cheking Closed, try reconnect...");
    WiFi.begin(ssid, password); // Wi-Fi 재접속 시도

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000); // 1초 대기
      Serial.println("재접속 시도 중...");
    }

    Serial.println("WiFi connect.");
    Serial.print("IP 주소: ");
    Serial.println(WiFi.localIP());
  }
};