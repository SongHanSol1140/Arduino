// wifi_mqtt.cpp
#include "wifi_mqtt.h"
#include "variables.h"
#include "pinControl.h"
#include "switch.h"
#include "utils.h"

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
    client.subscribe(coldbrewMachine, 2);
    client.subscribe(middleServer1_Response, 2);
    client.onMessage(messageReceived);
    client.loop();
    sendStatus();
  } else {
    client.loop();
    sendStatus();
  }
};

void initMachineValue() {
  client.publish(coldbrewSetup, "initInfo", false, 1);
};





// Process1 enum을 문자열로 변환
const char* processToString1(Process1 process) {
  switch (process) {
    case NONE: return "NONE";
    case COFFEE_CLEANING: return "COFFEE_CLEANING";
    case COFFEE_LOWER_CLEANING: return "COFFEE_LOWER_CLEANING";
    case COFFEE_CYCLE_CLEANING: return "COFFEE_CYCLE_CLEANING";
    case COLD_BREW_CLEANING: return "COLD_BREW_CLEANING";
    case COLD_BREW_LINE_CLEANING1: return "COLD_BREW_LINE_CLEANING1";
    case COLD_BREW_LINE_CLEANING2: return "COLD_BREW_LINE_CLEANING2";
    case COFFEE_EXTRACTION: return "COFFEE_EXTRACTION";
    case COFFEE_COOLING: return "COFFEE_COOLING";
    case COFFEE_TRANSFER: return "COFFEE_TRANSFER";
    case BOTTLE_TRANSFER: return "BOTTLE_TRANSFER";
    case BREWED_EXTRACTION: return "BREWED_EXTRACTION";
    case BREWED_COOLING: return "BREWED_COOLING";
    case BREWED_TRANSFER: return "BREWED_TRANSFER";
    case COLD_BREW_EXTRACTION: return "COLD_BREW_EXTRACTION";
    case COLD_BREW_COOLING: return "COLD_BREW_COOLING";
    case COLD_BREW_TRANSFER: return "COLD_BREW_TRANSFER";
    default: return "UNKNOWN";
  }
}

// Process2 enum을 문자열로 변환
const char* processToString2(Process2 process) {
  switch (process) {
    case CLEANING: return "CLEANING";
    case COLDBREW: return "COLDBREW";
    case COFFEE: return "COFFEE";
    default: return "UNKNOWN";
  }
}





void sendStatus() {
  StaticJsonDocument<1024> doc;
  doc["hash1"] = digitalRead(hash1) ? true : false;
  doc["hash2"] = digitalRead(hash2) ? true : false;
  doc["hash3"] = digitalRead(hash3) ? true : false;
  doc["hash4"] = digitalRead(hash4) ? true : false;
  doc["hash5"] = digitalRead(hash5) ? true : false;
  doc["hash6"] = digitalRead(hash6) ? true : false;
  doc["hash7"] = digitalRead(hash7) ? true : false;
  doc["hash8"] = digitalRead(hash8) ? true : false;
  doc["hash9"] = digitalRead(hash9) ? true : false;
  doc["hash10"] = digitalRead(hash10) ? true : false;
  doc["hash11"] = digitalRead(hash11) ? true : false;
  doc["hash12"] = digitalRead(hash12) ? true : false;
  doc["hash13"] = digitalRead(hash13) ? true : false;
  doc["hash14"] = digitalRead(hash14) ? true : false;
  doc["hash15"] = digitalRead(hash15) ? true : false;

  doc["heaterStatus"] = heaterStatus;
  doc["tmpCoolerPin"] = digitalRead(tmpCoolerPin) ? true : false;
  doc["coldbrewMachine"] = systemStatus;
  doc["coffeeMachine"] = coffeeMachineStatus;  // 추후에 커피머신에서 MQTT로 실시간으로 계속 전송해주는지 확인하고 뺄것
  doc["currentProcess"] = processToString1(currentProcess);
  doc["switchProcess"] = processToString2(switchProcess);
  doc["errorMessage"] = errorMessage;

  // JSON 문서를 문자열로 변환
  char jsonBuffer[1024];
  serializeJson(doc, jsonBuffer);

  client.publish(coldbrewController, jsonBuffer);
  if (errorMessage != "") {
    errorMessage = "";
  }
}

Process2 stringToProcess(const char* str) {
  if (strcmp(str, "CLEANING") == 0) return CLEANING;
  if (strcmp(str, "COLDBREW") == 0) return COLDBREW;
  if (strcmp(str, "COFFEE") == 0) return COFFEE;
  return CLEANING;  // 기본값
}
void messageReceived(String& topic, String& payload) {
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
    if (topic == coldbrewMachine) {
      if (first == coldbrewMachine && second == "orderCoffeeMachineCleaning") {
        Serial.println("커피머신 세정 MQTT");
        orderCoffeeMachineCleaning();
      }
      if (first == coldbrewMachine && second == "orderCoffeeMachineLowerCleaning") {
        Serial.println("커피머신 하단부 세정 MQTT");
        orderCoffeeMachineLowerCleaning();
      }
      if (first == coldbrewMachine && second == "orderCfCycleCleaning") {
        Serial.println("콜드브루머신 디카페인 사이클 세정 MQTT");
        orderCfCycleCleaning();
      }
      if (first == coldbrewMachine && second == "orderColdBrewCleaning") {
        Serial.println("콜드브루머신 본체 세정 MQTT");
        orderColdBrewCleaning();
      }
      if (first == coldbrewMachine && second == "orderColdBrewLineCleaningOne") {
        Serial.println("콜드브루머신 라인1 세정 MQTT");
        orderColdBrewLineCleaningOne();
      }
      if (first == coldbrewMachine && second == "orderColdBrewLineCleaningTwo") {
        Serial.println("콜드브루머신 라인2 세정 MQTT");
        orderColdBrewLineCleaningTwo();
      }


      if (first == coldbrewMachine && second == "orderBrewedExtraction") {
        Serial.println("브루드 커피 추출 MQTT");
        orderBrewedExtraction();
      }
      if (first == coldbrewMachine && second == "orderBrewedCooling") {
        Serial.println("브루드커피 냉각 MQTT");
        orderBrewedCooling();
      }
      if (first == coldbrewMachine && second == "orderBrewedTransfer") {
        Serial.println("브루드커피 이송 MQTT");
        orderBrewedTransfer();
      }
      if (first == coldbrewMachine && second == "orderColdBrewExtraction") {
        Serial.println("콜드브루 추출 MQTT");
        orderColdBrewExtraction();
      }
      if (first == coldbrewMachine && second == "orderColdBrewCooling") {
        Serial.println("콜드브루 냉각 MQTT");
        orderColdBrewCooling();
      }
      if (first == coldbrewMachine && second == "orderColdBrewTransfer") {
        Serial.println("콜드브루 이송 MQTT");
        orderColdBrewTransfer();
      }
      if (first == coldbrewMachine && second == "orderCfExtraction") {
        Serial.println("디카페인 추출 MQTT");
        orderCfExtraction();
      }
      if (first == coldbrewMachine && second == "orderCfCooling") {
        Serial.println("디카페인 냉각 MQTT");
        orderCfCooling();
      }
      if (first == coldbrewMachine && second == "orderCfTransfer") {
        Serial.println("디카페인 이송 MQTT");
        orderCfTransfer();
      }
      if (first == coldbrewMachine && second == "orderBottleTransfer") {
        Serial.println("냉장고에서 이송 MQTT");
        orderBottleTransfer();
      }



      // 스위치 컨트롤
      if (first == "switchProcess" && second == "CLEANING") {
        Serial.println("switchProcess = CLEANING;");
        switchProcess = CLEANING;
      } else if (first == "switchProcess" && second == "COLDBREW") {
        Serial.println("switchProcess = COLDBREW");
        switchProcess = COLDBREW;
      } else if (first == "switchProcess" && second == "COFFEE") {
        Serial.println("switchProcess = COFFEE");
        switchProcess = COFFEE;
      }
    }

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
    // 온도 입력
    if (doc.containsKey("tmpCfInput")) tmpCfInput = doc["tmpCfInput"];
    if (doc.containsKey("tmpCBInput")) tmpCBInput = doc["tmpCBInput"];
    // 각 온도계 출력량
    if (doc.containsKey("tmpCfOutput")) tmpCfOutput = doc["tmpCfOutput"];
    if (doc.containsKey("tmpCBOutput")) tmpCBOutput = doc["tmpCBOutput"];
    // 각 온도계 설정값(여기에 설정된 온도를 목표로 출력을 내보냄)
    if (doc.containsKey("tmpSetCfP")) tmpSetCfP = doc["tmpSetCfP"];
    if (doc.containsKey("tmpSetCBP")) tmpSetCBP = doc["tmpSetCBP"];
    // 온도계 출력제한    
    if (doc.containsKey("tmpCfOLimit")) tmpCfOLimit = doc["tmpCfOLimit"];
    if (doc.containsKey("tmpCBOLimit")) tmpCBOLimit = doc["tmpCBOLimit"];
    // 온도 설정변수
    if (doc.containsKey("tmpCf_CO")) tmpCf_CO = doc["tmpCf_CO"]; // 디카페인 설정온도
    if (doc.containsKey("tmpCB_EX")) tmpCB_EX = doc["tmpCB_EX"]; //콜드브루 추출온도
    if (doc.containsKey("tmpCB_CO")) tmpCB_CO = doc["tmpCB_CO"]; // 콜드브루 냉각온도
    if (doc.containsKey("tmpBr_EX")) tmpBr_EX = doc["tmpBr_EX"]; //브루드 추출온도
    if (doc.containsKey("tmpBr_CO")) tmpBr_CO = doc["tmpBr_CO"]; // 브루드 냉각온도


    // CT
    if (doc.containsKey("ctCfScale")) ctCfScale = doc["ctCfScale"];
    if (doc.containsKey("ctCBScale")) ctCBScale = doc["ctCBScale"];
    if (doc.containsKey("ctCoolerScale")) ctCoolerScale = doc["ctCoolerScale"];
    if (doc.containsKey("ctCfLimit")) ctCfLimit = doc["ctCfLimit"];
    if (doc.containsKey("ctCBLimit")) ctCBLimit = doc["ctCBLimit"];
    if (doc.containsKey("ctCoolerLimit")) ctCoolerLimit = doc["ctCoolerLimit"];
    if (doc.containsKey("ctCfInputV")) ctCfInputV = doc["ctCfInputV"];
    if (doc.containsKey("ctCBInputV")) ctCBInputV = doc["ctCBInputV"];
    if (doc.containsKey("ctCoolerInputV")) ctCoolerInputV = doc["ctCoolerInputV"];
    // 유량계
    if (doc.containsKey("flowLimit1")) flowLimit1 = doc["flowLimit1"];
    if (doc.containsKey("flowLimit2")) flowLimit2 = doc["flowLimit2"];
    if (doc.containsKey("totalFlow1")) totalFlow1 = doc["totalFlow1"];
    if (doc.containsKey("totalFlow2")) totalFlow2 = doc["totalFlow2"];
    // 레벨
    if (doc.containsKey("cfLevel")) cfLevel = doc["cfLevel"];
    if (doc.containsKey("coldbrewLevel")) coldbrewLevel = doc["coldbrewLevel"].as<int>();
    if (doc.containsKey("limitLevel")) limitLevel = doc["limitLevel"];
    if (doc.containsKey("limitLevelMin")) limitLevelMin = doc["limitLevelMin"];
    if (doc.containsKey("limitLevelMax")) limitLevelMax = doc["limitLevelMax"];


    
    if (doc.containsKey("cfCleanCount")) cfCleanCount = doc["cfCleanCount"];
    if (doc.containsKey("cfCleanTime")) cfCleanTime = doc["cfCleanTime"];
    if (doc.containsKey("cbCleanCount")) cbCleanCount = doc["cbCleanCount"];
    if (doc.containsKey("cbCleanTime")) cbCleanTime = doc["cbCleanTime"];
    if (doc.containsKey("timer1")) timer1 = doc["timer1"];
    if (doc.containsKey("timer2")) timer2 = doc["timer2"];
    if (doc.containsKey("timer3")) timer3 = doc["timer3"];
    if (doc.containsKey("timer4")) timer4 = doc["timer4"];

    // checkMqttValue();
  }
};
