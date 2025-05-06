// utils.cpp
#include "utils.h"
#include "variables.h"
#include "wifi_mqtt.h"
#include "webPage.h"
unsigned long previousMillis = 0;  // 이전 시간 저장
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
};

void TimerCheck(int Timer) {
  unsigned long startMillis = millis();
  while (millis() - startMillis < Timer * 1000) {
    client.loop();
    delay(100);  // 100ms 동안 대기
  }
}

void CoolingControl(bool trueFalse) {

  if (trueFalse) {
    client.publish(coldbrewSetup, "coolingStatus/true");
    // Serial.println("냉각기 실행 명령");
  } else {
    client.publish(coldbrewSetup, "coolingStatus/false");
    // Serial.println("냉각기 종료 명령");
  }
}
void CirculatingFlowMeterCheck() {
  // 순환 유량계 측정 시작
  Serial.println("순환 유량계 측정 시작");
  client.publish(coldbrewSetup, "totalFlow1/0.0");
  delay(1000);
  client.loop();
  while (totalFlow1 < flowLimit1) {
    // Serial.print("Current Flow: ");
    // Serial.println(totalFlow1);
    // Serial.print("Flow Limit: ");
    // Serial.println(flowLimit1);
    client.loop();
    delay(100);
  }
  Serial.println("순환 유량계 측정 종료");
}

void InflowFlowMeterCheck() {
  // 유입 유량계 측정시작
  Serial.println("유입 유량계 측정 시작");
  client.publish(coldbrewSetup, "totalFlow2/0.0");
  delay(1000);
  client.loop();
  while (totalFlow2 < flowLimit2) {
    // Serial.print("Current Flow: ");
    // Serial.println(totalFlow2);
    // Serial.print("Flow Limit: ");
    // Serial.println(flowLimit2);
    client.loop();
    delay(100);  // 100ms 동안 대기
  }
  // 유입 종료 메시지 출력
  Serial.println("유입 유량계 측정 종료");
}

void WaitDeacfHeating() {
  Serial.println("디카페인 히팅 시작");
  Serial.print("현재온도 : ");
  Serial.println(tmpInput1);
  Serial.print("목표온도 : ");
  Serial.println(setTmpPoint1);
  while (tmpInput1 <= setTmpPoint1) {
    // Serial.println(tmpInput1);
    // Serial.println(setTmpPoint1);
    client.loop();
    delay(100);
  }
  Serial.println("디카페인 히팅 완료");
}
void WaitDecafCooling() {
  Serial.println("디카페인 냉각 시작");
  Serial.print("현재온도 : ");
  Serial.println(tmpInput1);
  Serial.print("목표온도 : ");
  Serial.println(setTmpPoint1);
  while (tmpInput1 >= setTmpPoint1) {
    // Serial.println(tmpInput1);
    // Serial.println(setTmpPoint1);
    client.loop();
    delay(100);
  }
  Serial.println("디카페인 냉각 완료");
}
void WaitColdbrewHeating() {
  Serial.print("현재온도 : ");
  Serial.println(tmpInput2);
  Serial.print("목표온도 : ");
  Serial.println(setTmpPoint2);
  while (tmpInput2 <= setTmpPoint2) {
    // Serial.println(tmpInput2);
    // Serial.println(setTmpPoint2);
    client.loop();
    delay(100);
  }
}
void WaitColdbrewCooling() {
  Serial.print("현재온도 : ");
  Serial.println(tmpInput2);
  Serial.print("목표온도 : ");
  Serial.println(setTmpPoint2);
  while (tmpInput2 >= setTmpPoint2) {
    // Serial.println(tmpInput2);
    // Serial.println(setTmpPoint2);
    client.loop();
    delay(100);
  }
}
void orderDecafEspressoExtraction(int num){
  // 4. 커피머신 대기여부 확인
    getCoffeeMachineStatus();
    if (coffeeMachineStatus) {
      // 5. 커피머신 원두량 설정
      // setUsageCoffeeBean/1
      // setUsageCoffeeBean/2
      // setUsageCoffeeBean/3
      // setUsageCoffeeBean/4
      String payload = "coffeeMachine/setUsageCoffeeBean/" + String(num);
      client.publish(middleServer1, payload.c_str(), false, 2);  // 커피머신측 명령받는 ESP32측 설정 확인
      // 6. 커피머신 대기여부 확인
      getCoffeeMachineStatus();
      if (coffeeMachineStatus) {
        // 7. 커피머신 에스프레소 추출 명령
        client.publish(middleServer1, "coffeeMachine/espresso/1", false, 2);
      }
    }else{
      Serial.println("디카페인 에스프레소 추출중");
      delay(1000);
    }
}
void getCoffeeMachineStatus() {
  client.publish(middleServer1, "coffeeMachine/status", false, 2);
  previousMillis = millis();
  while (millis() - previousMillis < 1500) {
    client.loop();
  }  // MQTT 수신하며 1초간 대기
};



void checkMqttValue() {
  Serial.print("현재 온도1 : ");
  Serial.println(tmpInput1);
  Serial.print("현재 온도2 : ");
  Serial.println(tmpInput2);
  Serial.print("온도 출력1 : ");
  Serial.println(tmpOutput1);
  Serial.print("온도 출력2 : ");
  Serial.println(tmpOutput2);
  Serial.print("목표 온도1 : ");
  Serial.println(setTmpPoint1);
  Serial.print("목표 온도2 : ");
  Serial.println(setTmpPoint2);
  Serial.print("출력 제한1 : ");
  Serial.println(tmpOutLimit1);
  Serial.print("출력 제한2 : ");
  Serial.println(tmpOutLimit2);
  Serial.print("입력 스케일1 : ");
  Serial.println(scale1);
  Serial.print("입력 스케일2 : ");
  Serial.println(scale2);
  Serial.print("제한 스케일1 : ");
  Serial.println(limitScale1);
  Serial.print("제한 스케일2 : ");
  Serial.println(limitScale2);
  Serial.print("입력받은 출력1 : ");
  Serial.println(convertedScale1);
  Serial.print("입력받은 출력2 : ");
  Serial.println(convertedScale2);
  Serial.print("유량기 유량 제한값1 ml/s : ");
  Serial.println(flowLimit1);
  Serial.print("유량기 유량 제한값2 ml/s : ");
  Serial.println(flowLimit2);
  Serial.print("유량기 누적 송출량1 ml : ");
  Serial.println(totalFlow1);
  Serial.print("유량기 누적 송출량2 ml : ");
  Serial.println(totalFlow2);
  Serial.print("디카페인 레벨 센서 거리값 ml : ");
  Serial.println(decafLevel);
  Serial.print("콜드브루 레벨 센서 감지여부 ON(1)/OFF(0) : ");
  Serial.println(coldbrewLevel);
  Serial.print("Level 초음파 제한 값 : ");
  Serial.println(limitLevel);
  Serial.print("Level 초음파 빈 값 : ");
  Serial.println(limitLevelMin);
  Serial.print("Level 초음파 가득찬 값 : ");
  Serial.println(limitLevelMax);
  Serial.print("디카페인 세정 횟수 : ");
  Serial.println(decafCleanCount);
  Serial.print("디카페인 세정 시간 : ");
  Serial.println(decafCleanTime);
  Serial.print("콜드브루 세정 횟수 : ");
  Serial.println(cbCleanCount);
  Serial.print("콜드브루 세정 시간 : ");
  Serial.println(cbCleanTime);
  Serial.print("타이머1 : ");
  Serial.println(timer1);
  Serial.print("타이머2 : ");
  Serial.println(timer2);
  Serial.print("타이머3 : ");
  Serial.println(timer3);
  Serial.print("타이머4 : ");
  Serial.println(timer4);
  client.loop();
};
