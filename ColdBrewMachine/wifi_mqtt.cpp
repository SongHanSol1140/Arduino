// wifi_mqtt.cpp
#include "variables.h"
#include "wifi_mqtt.h"
// 와이파이
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";
// MQTT
const char mqttClientName[] = "ColdBrewMachine_Inner";
const char mqttUserName[] = "ColdBrewMachine_Inner";
const char mqttPassword[] = "ColdBrewMachine_Inner";

IPAddress address(192, 168, 0, 44);
WiFiClient net;
MQTTClient client(1024, 512);
// 읽기 버퍼 1024바이트, 쓰기 버퍼 128바이트 => 설정안하면 버퍼가 작아서 못받음 기본값 128바이트

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI Connect");
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 10);  // 고정 IP 주소
    const IPAddress gateway(192, 168, 0, 1);    // 게이트웨이 주소
    const IPAddress subnet(255, 255, 255, 0);   // 서브넷 마스크
    if (!WiFi.config(local_IP, gateway, subnet)) {
      Serial.println("STA Failed to configure");
    }  // 고정IP 설정 끝
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

void setMqtt() {
  if (!client.connected()) {
    Serial.println("MQTT Connect");
    client.begin(address, net);
    while (!client.connect(mqttClientName, mqttUserName, mqttPassword)) {
      Serial.println("MQTT connecting...");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    client.subscribe("coldbrewMachine", 2);
    client.subscribe("middleServer1_Response", 2);
    // client.onMessage(messageReceived);
    client.loop();
    // sendStatus();
  } else {
    client.loop();
    // sendStatus();
  }
};
