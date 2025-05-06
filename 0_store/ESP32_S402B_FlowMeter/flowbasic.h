// #include "variables.h"
// #include "flowSensor.h"

// void IRAM_ATTR pulseCounter() {
//   pulseCount++;
// }

// void calculateFlow() {
//   if ((millis() - checkTime) > 1000) {  // 0.1초마다 계산 업데이트
//     detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));

//     // 경과 시간 계산 (0.초 단위)
//     nowTime += 1.0;

//     // 유량 계산
//     flowRate = ((1000.0 / (millis() - checkTime)) * pulseCount) / 38;

//     // 리터 단위로 변환
//     flowMilliLitres = (flowRate / 60) * 1000;

//     // 총 유량 누적
    
//     totalMilliLitres += flowMilliLitres;

//     // 결과 출력
//     Serial.print("Time: ");
//     Serial.print(nowTime, 1);  // 소수점 1자리까지 출력
//     Serial.print(" seconds\t");

//     Serial.print("Flow rate: ");
//     Serial.print(flowRate, 3); // 소수점 3자리까지 출력
//     Serial.print(" L/min\t");

//     Serial.print("Output Liquid Quantity: ");
//     Serial.print(totalMilliLitres, 3); // 소수점 3자리까지 출력
//     Serial.print(" mL / ");
//     Serial.print(totalMilliLitres / 1000.0, 3); // 소수점 3자리까지 출력
//     Serial.println(" L");

//     // 변수 초기화
//     pulseCount = 0;
//     checkTime = millis();

//     // 인터럽트 다시 활성화
//     attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
//   }
// }
