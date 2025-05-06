// .ino
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include "variables.h"

#include "wifi_mqtt.h"
#include "lguTCP.h"


void setup() {
  Serial.begin(115200);
  delay(100);

  // ① Centrex 비밀번호 SHA-512 해시로 변환


  // WiFi 및 MQTT 설정
  setWifi();
  // WiFi.begin(wifi_ssid, wifi_password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  // TCP 서버 초기화
  initTCPServer();
  Serial.println("출입문 시스템 Setup");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  // TCP 클라이언트 처리
  handleTCPClients();
  delay(10);

}
