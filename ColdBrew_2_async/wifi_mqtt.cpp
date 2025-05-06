// wifi_mqtt.cpp
#include "wifi_mqtt.h";
#include "variables.h";
#include "pinControl.h";
#include "utils.h";




IPAddress address(192, 168, 0, 44);
WiFiClient net;
MQTTClient client(1024, 256);
// 읽기 버퍼 1024바이트, 쓰기 버퍼 512바이트 => 설정안하면 버퍼가 작아서 못받음 기본값 128바이트

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 10);  // 고정 IP 주소
    const IPAddress gateway(192, 168, 0, 1);    // 게이트웨이 주소
    const IPAddress subnet(255, 255, 255, 0);   // 서브넷 마스크
    if (!WiFi.config(local_IP, gateway, subnet)) {
      Serial.println("STA Failed to configure");
    }  // 고정IP 설정 끝
    WiFi.reconnect();
    int count = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("connecting wifi...");
      delay(1000);
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("연결 실패");
    } else {
      Serial.print("Wifi IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("WIFI connected!");
    }
  }
};

void setMqtt() {
  if (!client.connected()) {
    client.begin(address, net);
    while (!client.connect(mqttClientName)) {
      Serial.print("\nconnecting...");
      Serial.print(".");
      delay(1000);
    }
    Serial.println("MQTT connected!");
    client.subscribe(coldbrewMachine, 1);
    client.subscribe(middleServer1_Response, 1);
    client.onMessage(messageReceived);
    client.loop();
  } else {
    client.loop();
  }
};
void initMachineValue() {
  client.loop();
  client.publish(coldbrewSetup, "initInfo", false, 1);
  client.loop();
};

void messageReceived(String &topic, String &payload) {


  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  // Serial.println(payload);

  // JSON 데이터 수신 여부 확인
  DynamicJsonDocument doc(1024);  // 크기를 충분히 크게 설정
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    // JSON이 아닐 경우
    String first = Split(payload, '/', 0);
    String second = Split(payload, '/', 1);
    String third = Split(payload, '/', 2);
    String fourth = Split(payload, '/', 3);
    bool boolThird = third;
    if(third == "true"){
      boolThird = true;
    }else{
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


      switch (currentProcess) {
        // 0. 대기상태 = NONE
        case NONE:
          if (first == "coffeeMachine" && second == "status" && boolThird) {
            coffeeMachineStatus = true;
          } else {
            coffeeMachineStatus = false;
          }
          break;
        // 1. 커피머신 세정
        case COFFEE_CLEANING:
          if (first == "coffeeMachine" && second == "status" && boolThird) {
            coffeeMachineStatus = true;
          }else{
            coffeeMachineStatus = false;
          }
          break;
        // 2. 커피머신 하단부 세정 로직
        case COFFEE_LOWER_CLEANING:
          if (first == "coffeeMachine" && second == "status" && boolThird) {
            Serial.println("커피머신 하단부 세정 종료");
            client.loop();
            unsigned long startMillis = millis();
            while (millis() - startMillis < timer2 * 1000) {
              client.loop();
              delay(100);  // 100ms 동안 대기
            }
            client.loop();
            controlPin(hash12, false);
            controlPin(hash21, false);
            Serial.print("#12 #21핀 OFF");
            Serial.print("#12 #21핀 확인 : ");
            Serial.print(digitalRead(hash12));
            Serial.print(" / ");
            Serial.println(digitalRead(hash12));

            currentProcess = NONE;
            systemStatus = true;
            coffeeMachineStatus = false;
          }
          break;
        // 디카페인 사이클 세정 로직
        case DECAF_CYCLE_CLEANING:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 콜드브루 본체 세정
        case COLD_BREW_CLEANING:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 콜드브루 라인1 세정
        case COLD_BREW_LINE_CLEANING1:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 콜드브루 라인2 세정
        case COLD_BREW_LINE_CLEANING2:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 브루드커피 추출
        case BREWED_EXTRACTION:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 브루드커피 냉각
        case BREWED_COOLING:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 브루드커피 이송
        case BREWED_TRANSFER:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 콜드브루 추출
        case COLD_BREW_EXTRACTION:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 14. 콜드브루 냉각
        case COLD_BREW_COOLING:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 15. 브루드커피 이송
        case COLD_BREW_TRANSFER:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 16. 디카페인 추출
        case DECAF_EXTRACTION:
          if (first == "coffeeMachine" && second == "status" && boolThird) {
            Serial.println("커피머신 상태확인");
            coffeeMachineStatus = true;
          }
          break;
        // 17. 디카페인 냉각
        case DECAF_COOLING:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 18. 디카페인 이송
        case DECAF_TRANSFER:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
        // 19. 디카페인 냉장고에서 이송
        case DECAF_TRANSFER_FROM_FRIDGE:
          // 함수내에서 자체 종료됨 => 외부정보를 받아올필요 없음
          break;
      }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
