// wifiSetup.h
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

// 접속할 와이파이 / 비밀번호
const char* ssid = "NNX2-2.4G";
const char *password = "$@43skshslrtm";

int serverPort =  80;
WebServer server(serverPort);

void setWifi();
void reconnectWifi();

// 와이파이 접속
void setWifi(){
  Serial.println("ESP32 WEB Start");
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

// 와이파이 재접속 함수 구현
void reconnectWifi(){
  // Wi-Fi가 연결되어 있지 않다면
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