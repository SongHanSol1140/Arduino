// wifi_mqtt.cpp
#include "wifi_mqtt.h";
#include "variables.h";
#include "pinControl.h";
#include "utils.h";

IPAddress address(192, 168, 0, 44);
WiFiClient net;
MQTTClient client(1024, 128);
// 읽기 버퍼 1024바이트, 쓰기 버퍼 128바이트 => 설정안하면 버퍼가 작아서 못받음 기본값 128바이트

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 10);  // 고정 IP 주소
    const IPAddress gateway(192, 168, 0, 1);   // 게이트웨이 주소
    const IPAddress subnet(255, 255, 255, 0);  // 서브넷 마스크
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
// MQTT 토픽
void setMqtt() {
  if (!client.connected()) {
    client.begin(address, net);
    while (!client.connect("coldbrewESP32_2", "coldbrewESP32_2", "coldbrewESP32_2")) {
    // while (!client.connect(mqttClientName)) {
      Serial.println("MQTT connecting...");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    client.subscribe(coldbrewSetup, 2);
    client.onMessage(messageReceived);
  }else{
    client.loop();
  }
}


void initMachineValue() {
  client.loop();
  client.publish(coldbrewSetup, "initInfo", false, 1);
  client.loop();
};

void messageReceived(String &topic, String &payload) {
  // Serial.print(topic);
  // Serial.println(payload);

  // JSON 데이터 수신 여부 확인
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    // JSON이 아닐 경우
    String first = Split(payload, '/', 0);
    String second = Split(payload, '/', 1);
    String third = Split(payload, '/', 2);
    String fourth = Split(payload, '/', 3);
    bool boolThird = third;
    if (third == "true") {
      boolThird = true;
    } else {
      boolThird = false;
    }
    // String fifth = Split(payload, '/', 4);

    if (topic == middleServer1_Response) {
      Serial.println(payload);
      // Serial.println(first);
      // Serial.println(second);
      // Serial.println(third);
      // 언제나 hash12를 off할수잇도록 조건생성
      if (first == "coffeeMachine" && second == "hash12" && boolThird) {
        controlPin(hash12, true);
      } else {
        controlPin(hash12, false);
      }

      if (first == "coffeeMachine" && second == "status" && boolThird) {
        coffeeMachineStatus = true;
      } else {
        coffeeMachineStatus = false;
      }
    }
    return;
  }

  // JSON 데이터 수신
  if (topic == coldbrewMachine) {
    // Serial.println(payload);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    if (doc.containsKey("tmpInput1")) tmpInput1 = doc["tmpInput1"];
    if (doc.containsKey("tmpInput2")) tmpInput2 = doc["tmpInput2"];
    if (doc.containsKey("tmpOutput1")) tmpOutput1 = doc["tmpOutput1"];
    if (doc.containsKey("tmpOutput2")) tmpOutput2 = doc["tmpOutput2"];
    if (doc.containsKey("setTmpPoint1")) setTmpPoint1 = doc["setTmpPoint1"];
    if (doc.containsKey("setTmpPoint2")) setTmpPoint2 = doc["setTmpPoint2"];
    if (doc.containsKey("tmpOutLimit1")) tmpOutLimit1 = doc["tmpOutLimit1"];
    if (doc.containsKey("tmpOutLimit2")) tmpOutLimit2 = doc["tmpOutLimit2"];
    if (doc.containsKey("scale1")) scale1 = doc["scale1"];
    if (doc.containsKey("scale2")) scale2 = doc["scale2"];
    if (doc.containsKey("limitScale1")) limitScale1 = doc["limitScale1"];
    if (doc.containsKey("limitScale2")) limitScale2 = doc["limitScale2"];
    if (doc.containsKey("convertedScale1")) convertedScale1 = doc["convertedScale1"];
    if (doc.containsKey("convertedScale2")) convertedScale2 = doc["convertedScale2"];
    if (doc.containsKey("flowLimit1")) flowLimit1 = doc["flowLimit1"];
    if (doc.containsKey("flowLimit2")) flowLimit2 = doc["flowLimit2"];
    if (doc.containsKey("totalFlow1")) totalFlow1 = doc["totalFlow1"];
    if (doc.containsKey("totalFlow2")) totalFlow2 = doc["totalFlow2"];
    if (doc.containsKey("decafLevel")) decafLevel = doc["decafLevel"];
    if (doc.containsKey("coldbrewLevel")) coldbrewLevel = doc["coldbrewLevel"].as<int>();
    if (doc.containsKey("limitLevel")) limitLevel = doc["limitLevel"];
    if (doc.containsKey("limitLevelMin")) limitLevelMin = doc["limitLevelMin"];
    if (doc.containsKey("limitLevelMax")) limitLevelMax = doc["limitLevelMax"];
    if (doc.containsKey("decafCleanCount")) decafCleanCount = doc["decafCleanCount"];
    if (doc.containsKey("decafCleanTime")) decafCleanTime = doc["decafCleanTime"];
    if (doc.containsKey("cbCleanCount")) cbCleanCount = doc["cbCleanCount"];
    if (doc.containsKey("cbCleanTime")) cbCleanTime = doc["cbCleanTime"];
    if (doc.containsKey("timer1")) timer1 = doc["timer1"];
    if (doc.containsKey("timer2")) timer2 = doc["timer2"];
    if (doc.containsKey("timer3")) timer3 = doc["timer3"];
    if (doc.containsKey("timer4")) timer4 = doc["timer4"];
    // checkMqttValue();
  }
};
