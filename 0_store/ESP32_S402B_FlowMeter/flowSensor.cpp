// flowSensor.cpp

// 요구사항
// 1초 이상 누적유량에 변화 감지가 안될시 현재시간(지난시간)과 누적유량을 초기화
// 1초 이상 누적유량에 변화 감지가 안된 상태에서 유량이 감지될시 현재시간과 누적유량을 다시 0에서부터 시작
#include "variables.h"
#include "flowSensor.h"
void IRAM_ATTR pulseCounter() {
  pulseCount++;
  lastPulseTime = millis();

  // 만약 이전에 흐름이 멈춘 상태였거나 아직 유량 측정이 시작되지 않은 상태였다면
  // 새로 유량 시작: 0부터 다시 시작
  if (!isFlowing) {
    // 흐름 시작
    isFlowing = true;
    if (wasFlowStopped) {
      // 이전에 멈춰있었다면 다시 0부터 시작
      totalMilliLitres = 0.0;
      nowTime = 0.0;
      wasFlowStopped = false;
    }
  }
}

void calculateFlow() {
  // 1초마다 계산
  if ((millis() - checkTime) > 100) {
    // 2초 이상 펄스(유량) 감지 없음 -> 유량 멈춤 상태 처리
    if (isFlowing && (millis() - lastPulseTime) > 2000) {
      // 유량 흐름 멈춤
      isFlowing = false;
      wasFlowStopped = true;
      // 이 시점에서 totalMilliLitres, nowTime은 그대로 유지(고정)
    }

    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));

    if (isFlowing) {
      // 흐르는 상태면 시간 및 유량 계속 계산
      nowTime += 0.1; // 초마다 업데이트
      flowRate = ((100.0 / (millis() - checkTime)) * pulseCount) / 38;
      flowMilliLitres = (flowRate / 60.0) * 1000.0;
      totalMilliLitres += flowMilliLitres;

      // Serial.print("Time: ");
      Serial.print(nowTime, 1);  // 소수점 1자리까지 출력
      // Serial.print(" seconds\t");
      Serial.print("\t");

      // Serial.print("Flow rate: ");
      // Serial.print(flowRate, 3); // 소수점 3자리까지 출력
      // Serial.print(" L/min\t");

      // Serial.print("Output Liquid Quantity: ");
      Serial.println(totalMilliLitres, 1); // 소수점 3자리까지 출력
      // Serial.println(" mL / ");
      // Serial.print(totalMilliLitres / 1000.0, 3); // 소수점 3자리까지 출력
      // Serial.println(" L");

    } else {
      // 흐르지 않는 상태일 때는 값을 고정한 상태로 아무것도 안함.
      // 필요하다면 멈춰있는 상태 로그를 남기거나 할 수 있음
    }

    pulseCount = 0;
    checkTime = millis();

    // attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);
  }
}