// wifiSetup.cpp
#include "wifiSetup.h"

IPAddress address(192, 168, 0, 44);
WiFiClient net;

// 와이파이
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";
void setWifi() {
  WiFi.setAutoReconnect(true);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI Connect");
    // // 고정 IP 설정 - 미사용시 주석처리
    // const IPAddress local_IP(192, 168, 0, 10);  // 고정 IP 주소
    // const IPAddress gateway(192, 168, 0, 1);    // 게이트웨이 주소
    // const IPAddress subnet(255, 255, 255, 0);   // 서브넷 마스크
    // if (!WiFi.config(local_IP, gateway, subnet)) {
    //   Serial.println("STA Failed to configure");
    // }  // 고정IP 설정 끝
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("connecting wifi...");
      delay(1000);
    }
    Serial.print("Wifi IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("WIFI connected!");
  }
};
