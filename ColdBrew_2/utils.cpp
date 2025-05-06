// utils.cpp
#include "utils.h"
#include "variables.h"
#include "wifi_mqtt.h"
#include <esp_heap_caps.h>
// 메모리체크
void printMemoryUsage() {
  size_t totalHeap = heap_caps_get_total_size(MALLOC_CAP_8BIT);
  size_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  size_t usedHeap = totalHeap - freeHeap;

  Serial.print("Total Heap: ");
  Serial.println(totalHeap);
  Serial.print("Free Heap: ");
  Serial.println(freeHeap);
  Serial.print("Used Heap: ");
  Serial.println(usedHeap);
}

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
    // printMemoryUsage();
    setWifi();
    setMqtt();
    yield();
    delay(100);  // 100ms 동안 대기
  }
}
// 냉각기 - 목표온도보다 높으면 냉각기를 켜고, 목표온도보다 tmpTolerance만큼 낮으면 냉각기를 끈다
void CoolingControl(double currentTemp, double targetTemp) {
  if (coolerStatus) {
    if (currentTemp >= targetTemp) {
      digitalWrite(tmpCoolerPin, HIGH);
      // Serial.println("냉각기 실행");
    } else if (currentTemp <= (targetTemp - tmpTolerance)) {
      digitalWrite(tmpCoolerPin, LOW);
      // Serial.println("냉각기 종료");
    }
  } else {
    digitalWrite(tmpCoolerPin, LOW);
  }
}

void CirculatingFlowMeterCheck() {
  // 순환 유량계 측정 시작
  Serial.println("순환 유량계 측정 시작");
  client.publish(coldbrewSetup, "totalFlow1/0.0");
  TimerCheck(1);
  while (totalFlow1 < flowLimit1) {
    setMqtt();
    setWifi();
    yield();
    delay(100);
  }
  Serial.println("순환 유량계 측정 종료");
}

void InflowFlowMeterCheck() {
  // 유입 유량계 측정시작
  Serial.println("유입 유량계 측정 시작");
  client.publish(coldbrewSetup, "totalFlow2/0.0");
  TimerCheck(1);
  while (totalFlow2 < flowLimit2) {
    // Serial.print("Current Flow: ");
    // Serial.println(totalFlow2);
    // Serial.print("Flow Limit: ");
    // Serial.println(flowLimit2);
    setMqtt();
    setWifi();
    yield();
    delay(100);  // 100ms 동안 대기
  }
  // 유입 종료 메시지 출력
  Serial.println("유입 유량계 측정 종료");
}
// 미사용
void WaitCfHeating() {
  Serial.println("디카페인 히팅 시작");
  Serial.print("현재온도 : ");
  Serial.println(tmpCfInput);
  Serial.print("목표온도 : ");
  Serial.println(tmpSetCfP);
  while (tmpCfInput <= tmpSetCfP) {
    // Serial.println(tmpCfInput);
    // Serial.println(tmpSetCfP);
    setMqtt();
    setWifi();
    CoolingControl(tmpCfInput, tmpSetCfP);
    yield();
    delay(100);
  }
  Serial.println("디카페인 히팅 완료");
}
void WaitCfCooling() {
  Serial.println("디카페인 냉각 시작");
  Serial.print("현재온도 : ");
  Serial.println(tmpCfInput);
  Serial.print("목표온도 : ");
  Serial.println(tmpSetCfP);
  while (tmpCfInput >= tmpSetCfP) {
    // Serial.println(tmpCfInput);
    // Serial.println(tmpSetCfP);
    setWifi();
    setMqtt();
    CoolingControl(tmpCfInput, tmpSetCfP);
    yield();
    delay(100);
  }
  Serial.println("디카페인 냉각 완료");
}

void WaitBrewedHeating() {
  tmpSetCBP = tmpBr_EX;
  Serial.println("히팅 시작");
  Serial.print("현재온도 : ");
  Serial.print(tmpCBInput);
  Serial.print(" / 목표온도 : ");
  Serial.println(tmpSetCBP);
  while (tmpCBInput <= tmpSetCBP) {
    // Serial.println(tmpCBInput);
    // Serial.println(tmpSetCBP);
    setWifi();
    setMqtt();
    CoolingControl(tmpCBInput, tmpSetCBP);
    yield();
    delay(100);
  }
  Serial.println("히팅 완료");
}
void WaitBrewedCooling() {
  tmpSetCBP = tmpBr_CO;
  Serial.println("냉각 시작");
  Serial.print("현재온도 : ");
  Serial.print(tmpCBInput);
  Serial.print(" / 목표온도 : ");
  Serial.println(tmpSetCBP);
  while (tmpCBInput >= tmpSetCBP) {
    // Serial.println(tmpCBInput);
    // Serial.println(tmpSetCBP);
    setMqtt();
    setWifi();
    CoolingControl(tmpCBInput, tmpSetCBP);
    yield();
    delay(100);
  }
  Serial.println("냉각 완료");
}
void WaitColdbrewHeating() {
  tmpSetCBP = tmpCB_EX;
  Serial.println("히팅 시작");
  Serial.print("현재온도 : ");
  Serial.print(tmpCBInput);
  Serial.print(" / 목표온도 : ");
  Serial.println(tmpSetCBP);
  while (tmpCBInput <= tmpSetCBP) {
    // Serial.println(tmpCBInput);
    // Serial.println(tmpSetCBP);
    setWifi();
    setMqtt();
    CoolingControl(tmpCBInput, tmpSetCBP);
    yield();
    delay(100);
  }
  Serial.println("히팅 완료");
}
void WaitColdbrewCooling() {
  tmpSetCBP = tmpCB_CO;
  Serial.println("냉각 시작");
  Serial.print("현재온도 : ");
  Serial.print(tmpCBInput);
  Serial.print(" / 목표온도 : ");
  Serial.println(tmpSetCBP);
  while (tmpCBInput >= tmpSetCBP) {
    // Serial.println(tmpCBInput);
    // Serial.println(tmpSetCBP);
    setMqtt();
    setWifi();
    CoolingControl(tmpCBInput, tmpSetCBP);
    yield();
    delay(100);
  }
  Serial.println("냉각 완료");
}

void getCoffeeMachineStatus() {
  client.publish(middleServer1, "coffeeMachine/status", false, 2);
  previousMillis = millis();
  while (millis() - previousMillis < 1000) {
    setMqtt();
    setWifi();
    yield();
    delay(100);
  }  // MQTT 수신하며 1초간 대기
};



void checkMqttValue() {
  // 온도
  Serial.print("현재 온도1 : ");
  Serial.println(tmpCfInput);
  Serial.print("현재 온도2 : ");
  Serial.println(tmpCBInput);
  Serial.print("온도 출력1 : ");
  Serial.println(tmpCfOutput);
  Serial.print("온도 출력2 : ");
  Serial.println(tmpCBOutput);
  Serial.print("목표 온도1 : ");
  Serial.println(tmpSetCfP);
  Serial.print("목표 온도2 : ");
  Serial.println(tmpSetCBP);
  Serial.print("디카페인 냉각기 출력 제한 : ");
  Serial.println(tmpCfOLimit);
  Serial.print("콜드브루 냉각기 출력 제한 : ");
  Serial.println(tmpCBOLimit);
  // CT
  Serial.print("ct 디카페인 스케일 : ");
  Serial.println(ctCfScale);
  Serial.print("ct 콜드브루 스케일 : ");
  Serial.println(ctCBScale);
  Serial.print("ct 냉동기 스케일 : ");
  Serial.println(ctCoolerScale);
  Serial.print("디카페인 출력제한 : ");
  Serial.println(ctCfLimit);
  Serial.print("콜드브루 출력제한 : ");
  Serial.println(ctCBLimit);
  Serial.print("냉동기 출력 제한 : ");
  Serial.println(ctCoolerLimit);
  Serial.print("ct 디카페인 펌프 출력 : ");
  Serial.println(ctCfInputV);
  Serial.print("ct 콜드브루 펌프 출력 : ");
  Serial.println(ctCBInputV);
  Serial.print("ct 냉동기 출력 : ");
  Serial.println(ctCoolerInputV);
  // 유량계
  Serial.print("유량기 유량 제한값1 ml/s : ");
  Serial.println(flowLimit1);
  Serial.print("유량기 유량 제한값2 ml/s : ");
  Serial.println(flowLimit2);
  Serial.print("유량기 누적 송출량1 ml : ");
  Serial.println(totalFlow1);
  Serial.print("유량기 누적 송출량2 ml : ");
  Serial.println(totalFlow2);
  Serial.print("디카페인 레벨 센서 거리값 ml : ");
  Serial.println(cfLevel);
  Serial.print("콜드브루 레벨 센서 감지여부 ON(1)/OFF(0) : ");
  Serial.println(coldbrewLevel);
  Serial.print("Level 초음파 제한 값 : ");
  Serial.println(limitLevel);
  Serial.print("Level 초음파 빈 값 : ");
  Serial.println(limitLevelMin);
  Serial.print("Level 초음파 가득찬 값 : ");
  Serial.println(limitLevelMax);
  Serial.print("디카페인 세정 횟수 : ");
  Serial.println(cfCleanCount);
  Serial.print("디카페인 세정 시간 : ");
  Serial.println(cfCleanTime);
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
