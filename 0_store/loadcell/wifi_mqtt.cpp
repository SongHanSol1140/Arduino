#include "wifi_mqtt.h"
#include "weightCheck.h"
#include "variables.h"
WiFiClient net;
MQTTClient client(1024, 1024);



// Wi-Fi 설정
void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 233);  // 고정 IP 주소
    const IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
    const IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
    if (!WiFi.config(local_IP, gateway, subnet)) {
      Serial.println("STA Failed to configure");
    }  // 고정IP 설정 끝
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
  if (!client.connected()) {
    client.begin(mqttAddress, net);
    while (!client.connect(mqttClientName, mqttUserName, mqttPassword)) {
      // while (!client.connect(mqttClientName)) {
      Serial.println("MQTT connecting...");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    client.subscribe(subscribeTopic);
    client.onMessage(messageReceived);
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


void messageReceived(String &topic, String &payload) {
  // Serial.println("incoming: " + topic + " - " + payload);

  String first = Split(payload, '/', 0);
  String second = Split(payload, '/', 1);

  if (first == "Reset") {
    ESP.restart();
  }
  if (first == "SetZeroScale") {
    Serial.print("setZeroScale : ");
    // 현재값으로 수동 영점잡기
    setZeroFactor(10);
    Serial.println(zeroFactor);
  }
  if (first == "SetCalibrationFactor") {
    // 보정값 입력
    Serial.print("setCalibrationFactor : ");
    useManual = true;
    calibration_factor = second.toFloat();
    Serial.println(calibration_factor);
  }
}

// 무게값 MQTT로 전송
void sendWeightMQTT(float weightValue) {
  client.publish(publishTopic, String(weightValue));
}
