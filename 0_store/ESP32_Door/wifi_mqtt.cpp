// wifi_mqtt.cpp
#include "wifi_mqtt.h"
#include "variables.h"
#include "door.h"
#include "max98357.h"

WiFiClient net;
MQTTClient mqttClient(1024, 1024);

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 미사용시 주석처리
    // 고정 IP 설정
    if (!WiFi.config(wifiIP, gateway, subnet, dns)) {
      Serial.println("STA Failed to configure");
    }
    // 고정IP 설정 끝

    WiFi.begin(wifi_ssid, wifi_password);
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
  if (!mqttClient.connected()) {
    mqttClient.begin(mqttAddress, net);
    while (!mqttClient.connect(mqttClientName, mqttUserName, mqttPassword)) {
      // while (!client.connect(mqttClientName)) {
      Serial.println("MQTT connecting...");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    mqttClient.subscribe(moduleTopic);
    mqttClient.onMessage(messageReceived);
  }
}






String Split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void messageReceived(String &topicName, String &payload) {
  Serial.println("incoming: " + topicName + " - " + payload);

  String first = Split(payload, '/', 0);
  String second = Split(payload, '/', 1);

  if (first == "openTime") {
    Serial.println("set optenTime");
    Serial.print(first);
    Serial.print(":");
    Serial.println(second);

    openTime = second.toInt();  // String 값을 int로 변환
  }
  if (first == "waitForOpenTime") {
    Serial.println("set waitForOpenTime");
    Serial.print(first);
    Serial.print(":");
    Serial.println(second);
    waitForOpenTime = second.toInt();  // String 값을 int로 변환
  }

  // 문 개방 명령
  if (first == "Open") {
    Serial.println("OpenDoor command received");
    // playWavNonBlocking("dingdong.wav");  // max98357
    OpenDoor(); // OpenDoor 함수 호출하여 문 개방
  }
}