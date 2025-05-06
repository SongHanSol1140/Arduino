#include "wifi_mqtt.h"
#include "variables.h"
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";

IPAddress address(192, 168, 0, 44);
WiFiClient net;
MQTTClient client(1024, 1024);


void setWifi() {
  
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.setAutoReconnect(true);
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 5);  // 고정 IP 주소
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
    while (!client.connect(mqttClientName, mqttUserName, mqttPassword)) {
    // while (!client.connect(mqttClientName)) {
      Serial.println("MQTT connecting...");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    client.subscribe(coldBrewSetup, 2);
    client.onMessage(messageReceived);
  }else{
    client.loop();
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
  Serial.println("incoming: " + topic + " - " + payload);

  String first = Split(payload, '/', 0);
  String second = Split(payload, '/', 1);
  // init
  if (first == "initInfo") {
    Serial.println("initInfo");
    sendStatus();
    // 온도
  } else if (first == "tmpSetCfP") {
    Serial.print("tmpSetCfP : ");
    tmpSetCfP = second.toDouble();
    Serial.println(tmpSetCfP);
    preferences.putDouble("tmpSetCfP", tmpSetCfP);
    sendStatus();
  } else if (first == "tmpSetCBP") {
    Serial.print("tmpSetCBP : ");
    tmpSetCBP = second.toDouble();
    Serial.println(tmpSetCBP);
    preferences.putDouble("tmpSetCBP", tmpSetCBP);
    sendStatus();
  } else if (first == "tmpCfOLimit") {
    Serial.print("tmpCfOLimit : ");
    tmpCfOLimit = second.toDouble();
    Serial.println(tmpCfOLimit);
    preferences.putDouble("tmpCfOLimit", tmpCfOLimit);
    sendStatus();
  } else if (first == "tmpCBOLimit") {
    Serial.print("tmpCBOLimit : ");
    tmpCBOLimit = second.toDouble();
    Serial.println(tmpCBOLimit);
    preferences.putDouble("tmpCBOLimit", tmpCBOLimit);
    sendStatus();
  } else if (first == "tmpCf_CO") {
    Serial.print("tmpCf_CO : ");
    tmpCf_CO = second.toDouble();
    Serial.println(tmpCf_CO);
    preferences.putDouble("tmpCf_CO", tmpCf_CO);
    sendStatus();
  } else if (first == "tmpCB_EX") {
    Serial.print("tmpCB_EX : ");
    tmpCB_EX = second.toDouble();
    Serial.println(tmpCB_EX);
    preferences.putDouble("tmpCB_EX", tmpCB_EX);
    sendStatus();
  } else if (first == "tmpCB_CO") {
    Serial.print("tmpCB_CO : ");
    tmpCB_CO = second.toDouble();
    Serial.println(tmpCB_CO);
    preferences.putDouble("tmpCB_CO", tmpCB_CO);
    sendStatus();
  } else if (first == "tmpBr_EX") {
    Serial.print("tmpBr_EX : ");
    tmpBr_EX = second.toDouble();
    Serial.println(tmpBr_EX);
    preferences.putDouble("tmpBr_EX", tmpBr_EX);
    sendStatus();
  } else if (first == "tmpBr_CO") {
    Serial.print("tmpBr_CO : ");
    tmpBr_CO = second.toDouble();
    Serial.println(tmpBr_CO);
    preferences.putDouble("tmpBr_CO", tmpBr_CO);
    sendStatus();

    // =========================================
    // CT
  } else if (first == "ctCfScale") {
    ctCfScale = second.toDouble();
    Serial.print("ctCfScale : ");
    Serial.println(second);
    preferences.putDouble("ctCfScale", ctCfScale);
    sendStatus();
  } else if (first == "ctCBScale") {
    ctCBScale = second.toDouble();
    Serial.print("ctCBScale : ");
    Serial.println(second);
    preferences.putDouble("ctCBScale", ctCBScale);
    sendStatus();
  } else if (first == "ctCoolerScale") {
    ctCoolerScale = second.toDouble();
    Serial.print("ctCoolerScale : ");
    Serial.println(second);
    preferences.putDouble("ctCoolerScale", ctCoolerScale);
    sendStatus();

  } else if (first == "ctCfLimit") {
    ctCfLimit = second.toDouble();
    Serial.print("ctCfLimit : ");
    Serial.println(second);
    preferences.putDouble("ctCfLimit", ctCfLimit);
    sendStatus();
  } else if (first == "ctCBLimit") {
    ctCBLimit = second.toDouble();
    Serial.print("ctCBLimit : ");
    Serial.println(second);
    preferences.putDouble("ctCBLimit", ctCBLimit);
    sendStatus();
  } else if (first == "ctCoolerLimit") {
    ctCoolerLimit = second.toDouble();
    Serial.print("ctCoolerLimit : ");
    Serial.println(second);
    preferences.putDouble("ctCoolerLimit", ctCoolerLimit);
    sendStatus();

  } else if (first == "ctCfInputV") {
    ctCfInputPercent = second.toDouble();
    Serial.print("ctCfInputPercent : ");
    Serial.println(second);
    preferences.putDouble("ctCfInputPercent", ctCfInputPercent);
    sendStatus();
  } else if (first == "ctCBInputPercent") {
    ctCBInputPercent = second.toDouble();
    Serial.print("ctCBInputPercent : ");
    Serial.println(second);
    preferences.putDouble("ctCBInputPercent", ctCBInputPercent);
    sendStatus();
  } else if (first == "ctCoolerInputPercent") {
    ctCoolerInputPercent = second.toDouble();
    Serial.print("ctCoolerInputPercent : ");
    Serial.println(second);
    preferences.putDouble("ctCoolerInputPercent", ctCoolerInputPercent);
    sendStatus();
    // 유량기 ml제한
  } else if (first == "totalFlow1") {
    totalFlow1 = second.toDouble();
    Serial.print("totalFlow1 : ");
    Serial.println(second);
    sendStatus();
  } else if (first == "totalFlow2") {
    totalFlow2 = second.toDouble();
    Serial.print("totalFlow2 : ");
    Serial.println(second);
    sendStatus();
  } else if (first == "flowLimit1") {
    flowLimit1 = second.toInt();
    Serial.print("flowLimit1 : ");
    Serial.println(second);
    preferences.putInt("flowLimit1", flowLimit1);
    sendStatus();
  } else if (first == "flowLimit2") {
    flowLimit2 = second.toInt();
    Serial.print("flowLimit2 : ");
    Serial.println(second);
    preferences.putInt("flowLimit2", flowLimit2);
    sendStatus();
    // Level 초음파 거리센서
  } else if (first == "limitLevel") {
    limitLevel = second.toInt();
    Serial.print("limitLevel : ");
    Serial.println(second);
    preferences.putInt("limitLevel", limitLevel);
    sendStatus();
  } else if (first == "limitLevelMin") {
    limitLevelMin = second.toInt();
    Serial.print("limitLevelMin : ");
    Serial.println(second);
    preferences.putInt("limitLevelMin", limitLevelMin);
    sendStatus();
  } else if (first == "limitLevelMax") {
    limitLevelMax = second.toInt();
    Serial.print("limitLevelMax : ");
    Serial.println(second);
    preferences.putInt("limitLevelMax", limitLevelMax);
    sendStatus();
  } else if (first == "cfCleanCount") {
    cfCleanCount = second.toInt();
    Serial.print("cfCleanCount : ");
    Serial.println(second);
    preferences.putInt("cfCleanCount", cfCleanCount);
    sendStatus();
    // 세정횟수 / 시간
  } else if (first == "cfCleanTime") {
    cfCleanTime = second.toInt();
    Serial.print("cfCleanTime : ");
    Serial.println(second);
    preferences.putInt("cfCleanTime", cfCleanTime);
    sendStatus();
  } else if (first == "cbCleanCount") {
    cbCleanCount = second.toInt();
    Serial.print("cbCleanCount : ");
    Serial.println(second);
    preferences.putInt("cbCleanCount", cbCleanCount);
    sendStatus();
  } else if (first == "cbCleanTime") {
    cbCleanTime = second.toInt();
    Serial.print("cbCleanTime : ");
    Serial.println(second);
    preferences.putInt("cbCleanTime", cbCleanTime);
    sendStatus();
  } else if (first == "timer1") {
    timer1 = second.toInt();
    Serial.print("timer1 : ");
    Serial.println(second);
    preferences.putInt("timer1", timer1);
    sendStatus();
  } else if (first == "timer2") {
    timer2 = second.toInt();
    Serial.print("timer2 : ");
    Serial.println(second);
    preferences.putInt("timer2", timer2);
    sendStatus();
  } else if (first == "timer3") {
    timer3 = second.toInt();
    Serial.print("timer3 : ");
    Serial.println(second);
    preferences.putInt("timer3", timer3);
    sendStatus();
  } else if (first == "timer4") {
    timer4 = second.toInt();
    Serial.print("timer4 : ");
    Serial.println(second);
    preferences.putInt("timer4", timer4);
    sendStatus();
  } else if (first == "heaterStatus") {
    if (second == "true") {
      heaterStatus = true;
    } else if (second == "false") {
      heaterStatus = false;
    }
    Serial.print("heaterStatus : ");
    Serial.println(heaterStatus);
  }
}


void sendStatus() {
    setMqtt();
    // StaticJsonDocument 사용
    StaticJsonDocument<1024> doc;
    // JSON 문서에 데이터 추가
    //온도
    doc["tmpCfInput"] = tmpCfInput;
    doc["tmpCBInput"] = tmpCBInput;
    doc["tmpCfOutput"] = tmpCfOutput;
    doc["tmpCBOutput"] = tmpCBOutput;
    doc["tmpSetCfP"] = tmpSetCfP;
    doc["tmpSetCBP"] = tmpSetCBP;
    doc["tmpCfOLimit"] = tmpCfOLimit;
    doc["tmpCBOLimit"] = tmpCBOLimit;
    doc["tmpCf_CO"] = tmpCf_CO;
    doc["tmpCB_EX"] = tmpCB_EX;
    doc["tmpCB_CO"] = tmpCB_CO;
    doc["tmpBr_EX"] = tmpBr_EX;
    doc["tmpBr_CO"] = tmpBr_CO;
    //CT
    doc["ctCfScale"] = ctCfScale;
    doc["ctCBScale"] = ctCBScale;
    doc["ctCoolerScale"] = ctCoolerScale;
    doc["ctCfLimit"] = ctCfLimit;
    doc["ctCBLimit"] = ctCBLimit;
    doc["ctCoolerLimit"] = ctCoolerLimit;
    doc["ctCfInputPercent"] = ctCfInputPercent;
    doc["ctCBInputPercent"] = ctCBInputPercent;
    doc["ctCoolerInputPercent"] = ctCoolerInputPercent;
    // 유량계
    doc["flowLimit1"] = flowLimit1;
    doc["flowLimit2"] = flowLimit2;
    doc["totalFlow1"] = totalFlow1;
    doc["totalFlow2"] = totalFlow2;
    doc["cfLevel"] = cfLevel;
    doc["coldbrewLevel"] = coldbrewLevel;
    doc["limitLevel"] = limitLevel;
    doc["limitLevelMin"] = limitLevelMin;
    doc["limitLevelMax"] = limitLevelMax;
    doc["cfCleanCount"] = cfCleanCount;
    doc["cfCleanTime"] = cfCleanTime;
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
  