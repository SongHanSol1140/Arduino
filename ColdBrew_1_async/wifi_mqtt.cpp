#include "wifi_mqtt.h"
#include "variables.h"
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";

IPAddress address(192, 168, 0, 44);
WiFiClient net;
MQTTClient client(1024, 1024);


void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 5);  // 고정 IP 주소
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
  client.begin(address, net);
  // while (!client.connect("ColdBrew_ESP32_1", "ColdBrew_ESP32_1", "public")) {
  while (!client.connect(mqttClientName)) {
    Serial.println("connecting...");
    delay(1000);
  }
  Serial.println("MQTT connected!");
  client.subscribe(coldBrewSetup, 1);
  client.onMessage(messageReceived);
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
  Serial.println("incoming: " + topic + " - " + payload);

  String first = Split(payload, '/', 0);
  String second = Split(payload, '/', 1);
  // init
  if (first == "initInfo") {
    Serial.println("initInfo");
    initMachineValue();
    // 온도
  } else if (first == "setTmpPoint1") {
    Serial.print("setTmpPoint1 : ");
    setTmpPoint1 = second.toDouble();
    Serial.println(setTmpPoint1);
    preferences.putDouble("setTmpPoint1", setTmpPoint1);
    initMachineValue();
  } else if (first == "setTmpPoint2") {
    Serial.print("setTmpPoint2 : ");
    setTmpPoint2 = second.toDouble();
    Serial.println(setTmpPoint2);
    preferences.putDouble("setTmpPoint2", setTmpPoint2);
    initMachineValue();
  } else if (first == "tmpOutLimit1") {
    Serial.print("tmpOutLimit1 : ");
    tmpOutLimit1 = second.toDouble();
    Serial.println(tmpOutLimit1);
    preferences.putDouble("tmpOutLimit1", tmpOutLimit1);
    initMachineValue();
  } else if (first == "tmpOutLimit2") {
    Serial.print("tmpOutLimit2 : ");
    tmpOutLimit2 = second.toDouble();
    Serial.println(tmpOutLimit2);
    preferences.putDouble("tmpOutLimit2", tmpOutLimit2);
    initMachineValue();

    // CT스케일
  } else if (first == "scale1") {
    scale1 = second.toDouble();
    Serial.print("scale1 : ");
    Serial.println(second);
    preferences.putDouble("scale1", scale1);
    initMachineValue();

  } else if (first == "scale2") {
    scale2 = second.toDouble();
    Serial.print("scale2 : ");
    Serial.println(second);
    preferences.putDouble("scale2", scale2);
    initMachineValue();
  } else if (first == "limitScale1") {
    limitScale1 = second.toInt();
    Serial.print("limitScale1 : ");
    Serial.println(second);
    preferences.putInt("limitScale1", limitScale1);
    initMachineValue();
  } else if (first == "limitScale2") {
    limitScale2 = second.toInt();
    Serial.print("limitScale2 : ");
    Serial.println(second);
    preferences.putInt("limitScale2", limitScale2);
    initMachineValue();
    // 유량기 ml제한
  } else if (first == "totalFlow1") {
    totalFlow1 = second.toDouble();
    Serial.print("totalFlow1 : ");
    Serial.println(second);
    initMachineValue();
  } else if (first == "totalFlow2") {
    totalFlow2 = second.toDouble();
    Serial.print("totalFlow2 : ");
    Serial.println(second);
    initMachineValue();
  } else if (first == "flowLimit1") {
    flowLimit1 = second.toInt();
    Serial.print("flowLimit1 : ");
    Serial.println(second);
    preferences.putInt("flowLimit1", flowLimit1);
    initMachineValue();
  } else if (first == "flowLimit2") {
    flowLimit2 = second.toInt();
    Serial.print("flowLimit2 : ");
    Serial.println(second);
    preferences.putInt("flowLimit2", flowLimit2);
    initMachineValue();
    // Level 초음파 거리센서
  } else if (first == "limitLevel") {
    limitLevel = second.toInt();
    Serial.print("limitLevel : ");
    Serial.println(second);
    preferences.putInt("limitLevel", limitLevel);
    initMachineValue();
  } else if (first == "limitLevelMin") {
    limitLevelMin = second.toInt();
    Serial.print("limitLevelMin : ");
    Serial.println(second);
    preferences.putInt("limitLevelMin", limitLevelMin);
    initMachineValue();
  } else if (first == "limitLevelMax") {
    limitLevelMax = second.toInt();
    Serial.print("limitLevelMax : ");
    Serial.println(second);
    preferences.putInt("limitLevelMax", limitLevelMax);
    initMachineValue();
  } else if (first == "decafCleanCount") {
    decafCleanCount = second.toInt();
    Serial.print("decafCleanCount : ");
    Serial.println(second);
    preferences.putInt("decafCleanCount", decafCleanCount);
    initMachineValue();
    // 세정횟수 / 시간
  } else if (first == "decafCleanTime") {
    decafCleanTime = second.toInt();
    Serial.print("decafCleanTime : ");
    Serial.println(second);
    preferences.putInt("decafCleanTime", decafCleanTime);
    initMachineValue();
  } else if (first == "cbCleanCount") {
    cbCleanCount = second.toInt();
    Serial.print("cbCleanCount : ");
    Serial.println(second);
    preferences.putInt("cbCleanCount", cbCleanCount);
    initMachineValue();
  } else if (first == "cbCleanTime") {
    cbCleanTime = second.toInt();
    Serial.print("cbCleanTime : ");
    Serial.println(second);
    preferences.putInt("cbCleanTime", cbCleanTime);
    initMachineValue();
  } else if (first == "timer1") {
    timer1 = second.toInt();
    Serial.print("timer1 : ");
    Serial.println(second);
    preferences.putInt("timer1", timer1);
    initMachineValue();
  } else if (first == "timer2") {
    timer2 = second.toInt();
    Serial.print("timer2 : ");
    Serial.println(second);
    preferences.putInt("timer2", timer2);
    initMachineValue();
  } else if (first == "timer3") {
    timer3 = second.toInt();
    Serial.print("timer3 : ");
    Serial.println(second);
    preferences.putInt("timer3", timer3);
    initMachineValue();
  } else if (first == "timer4") {
    timer4 = second.toInt();
    Serial.print("timer4 : ");
    Serial.println(second);
    preferences.putInt("timer4", timer4);
    initMachineValue();
  } else if (first == "coolingStatus") {
    if (second == "true") {
      coolingStatus = true;
    } else if (second == "false") {
      coolingStatus = false;
    }
    Serial.print("coolingStatus : ");
    Serial.println(coolingStatus);
  }
}

void updatePv() {
  // StaticJsonDocument 사용
  StaticJsonDocument<1024> doc;
  // 현재온도 / 목표온도 / PID출력
  doc["tmpInput1"] = tmpInput1;
  doc["tmpInput2"] = tmpInput2;
  doc["setTmpPoint1"] = setTmpPoint1;
  doc["setTmpPoint2"] = setTmpPoint2;
  doc["tmpOutput1"] = tmpOutput1;
  doc["tmpOutput2"] = tmpOutput2;
  // 제한유량 / 송출유량
  doc["totalFlow1"] = totalFlow1;
  doc["totalFlow2"] = totalFlow2;
  // 현재 pv값
  doc["decafLevel"] = decafLevel;
  doc["coldbrewLevel"] = digitalRead(coldbrewLevelPin);
  // 현재 송출량
  doc["totalFlow1"] = totalFlow1;
  doc["totalFlow2"] = totalFlow2;
  // JSON 문서를 문자열로 변환
  char jsonBuffer[1024];
  serializeJson(doc, jsonBuffer);
  // MQTT 클라이언트를 통해 JSON 메시지 전송
  client.publish(coldBrewMachine, jsonBuffer);
}
void initMachineValue() {
  // StaticJsonDocument 사용
  StaticJsonDocument<1024> doc;
  // JSON 문서에 데이터 추가
  doc["tmpInput1"] = tmpInput1;
  doc["tmpInput2"] = tmpInput2;
  doc["tmpOutput1"] = tmpOutput1;
  doc["tmpOutput2"] = tmpOutput2;
  doc["setTmpPoint1"] = setTmpPoint1;
  doc["setTmpPoint2"] = setTmpPoint2;
  doc["tmpOutLimit1"] = tmpOutLimit1;
  doc["tmpOutLimit2"] = tmpOutLimit2;
  doc["scale1"] = scale1;
  doc["scale2"] = scale2;
  doc["limitScale1"] = limitScale1;
  doc["limitScale2"] = limitScale2;
  doc["convertedScale1"] = convertedScale1;
  doc["convertedScale2"] = convertedScale2;
  doc["flowLimit1"] = flowLimit1;
  doc["flowLimit2"] = flowLimit2;
  doc["totalFlow1"] = totalFlow1;
  doc["totalFlow2"] = totalFlow2;
  doc["decafLevel"] = decafLevel;
  doc["coldbrewLevel"] = coldbrewLevel;
  doc["limitLevel"] = limitLevel;
  doc["limitLevelMin"] = limitLevelMin;
  doc["limitLevelMax"] = limitLevelMax;
  doc["decafCleanCount"] = decafCleanCount;
  doc["decafCleanTime"] = decafCleanTime;
  doc["cbCleanCount"] = cbCleanCount;
  doc["cbCleanTime"] = cbCleanTime;
  doc["timer1"] = timer1;
  doc["timer2"] = timer2;
  doc["timer3"] = timer3;
  doc["timer4"] = timer4;

  // JSON 문서를 문자열로 변환
  char jsonBuffer[1024];
  serializeJson(doc, jsonBuffer);

  // 디버깅: JSON 데이터를 시리얼 모니터에 출력
  // Serial.println("Publishing JSON data:");
  // serializeJsonPretty(doc, Serial);
  // Serial.println();
  // 디버깅: JSON 버퍼를 시리얼 모니터에 출력
  // Serial.println("JSON buffer:");
  // Serial.println(jsonBuffer);

  // MQTT 클라이언트를 통해 JSON 메시지 전송
  client.publish(coldBrewMachine, jsonBuffer);
}
