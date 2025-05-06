// function.cpp
#include <Arduino.h>
#include "variables.h"

// 기준 전압 계산 (전압 분배기를 통해 계산됨)
float getVoltage(float rawAdcValue) {
  float currentVoltage = (rawAdcValue / 1023.0) * 5.0;
  return currentVoltage;
  // return currentVoltage * voltageMultiplier;  // 전압 분배기 공식 적용
}


// 무부하 상태 ACS712 오프셋 보정 함수
void calibrateACS712() {
  float sum = 0;  // 정밀도를 위해 float로 변경
  for (int i = 0; i < sampleCount; i++) {
    float adcValue = analogRead(ACS712_PIN);      // 전류 센서의 ADC 값 읽기
    float currentVoltage = getVoltage(adcValue);  // 전압 변환
    sum += currentVoltage;                        // 전압 값 누적
    delayMicroseconds(10);
  }
  float averageADC = sum / sampleCount;  // 평균 전압 계산
  offsetVoltage = averageADC;            // 오프셋 값을 평균 전압으로 설정
  Serial.print("오프셋 전압 : ");
  Serial.print(offsetVoltage);
  Serial.println("V");
  Serial.println("PID Setup Clear");
  delay(1000);
}





// void setupPID() {
//   // PWM 설정
//   ledcAttach(PWM_PIN, pwmFreq, pwmResolution);
//   // PID 제어 설정
//   Serial.println("PWM Control Start");
//   Serial.println("Mode AUTOMATIC");
//   myPID.SetMode(AUTOMATIC);
//   // Serial.println("Mode MANUAL");
//   // myPID.SetMode(MANUAL);
//   myPID.SetOutputLimits(25, 255);
//   targetPWM = targetHz / 15000 * 255;
//   Serial.print("목표 Hz : ");
//   Serial.println(targetHz);

//   Serial.println("PID Setup Clear");
//   delay(1000);
// }

void setupESP32() {
  // 스위치 버튼
  // pinMode(SWITCH_PIN, INPUT_PULLUP);
  // ACS712 캘리브레이션?
  calibrateACS712();
  // 모터압력 PID핀 설정
  // setupPID();
}










// void switchControl() {
//   // PWM 출력 상태 관리
//   currentButtonState = digitalRead(SWITCH_PIN);
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     isRunning = !isRunning;
//     Serial.println("Button Pressed: Toggled");
//     Serial.print("PWM 출력 상태: ");
//     Serial.println(isRunning);
//     if (isRunning) {
//       Serial.println("AUTOMATIC");
//       myPID.SetMode(AUTOMATIC);
//     } else {
//       Serial.println("MANUAL");
//       myPID.SetMode(MANUAL);
//     }
//   }
//   lastButtonState = currentButtonState;  // 상태 업데이트
// }











// void moterPIDControl() {
//   int analogValue = analogRead(ANALOG_PIN);
//   currentPWM = (double)analogValue / 4095.0 * 255.0;
//   if (isRunning) {
//     targetPWM = targetHz / 15000 * 255;
//     // 아날로그 값(0~4095)을 목표 듀티 사이클 값(0~255)으로 변환
//     myPID.Compute();
//     // pwmOutput = 255; // 테스트용 듀티사이클 100%
//     ledcWrite(PWM_PIN, (int)pwmOutput);
//     Serial.println("ON");  // 테스트 종료시 주석처리
//   } else {
//     targetPWM = 0;
//     pwmOutput = 0;
//     ledcWrite(PWM_PIN, 0);
//     Serial.println("OFF");  // 테스트 종료시 주석처리
//   }

// Serial.print("currentPWM : ");
// Serial.println(currentPWM);
// Serial.print("targetPWM : ");
// Serial.println(targetPWM);
// Serial.print("pwmOutput : ");
// Serial.println(pwmOutput);


// Serial.print("모터 입력Hz : ");
// Serial.println(currentPWM / 255 * 15000);
// Serial.print("모터 출력Hz: ");
// Serial.println(pwmOutput / 255 * 15000);
// }




void getRMS() {
  float ampereSum = 0;
  float voltageSum = 0;
  for (int i = 0; i < sampleCount; i++) {
    int adcValue = analogRead(ACS712_PIN);
    float currentVoltage = getVoltage(adcValue);
    // 전압(V)계산
    voltageSum += currentVoltage * currentVoltage;
    // 전류(A)계산
    float zeroValue = currentVoltage - offsetVoltage;
    float currentAmpere = zeroValue / sensitivity;
    ampereSum += currentAmpere * currentAmpere;
    delayMicroseconds(10);
  }
  acs712Voltage = sqrt(voltageSum / sampleCount);  // V RMS값 계산
  acs712Ampere = sqrt(ampereSum / sampleCount);    // A RMS값 계산

  Serial.print("ACS712 출력: ");
  Serial.print(acs712Voltage);
  Serial.println("V");
  Serial.print("ACS712 전류계산: ");
  Serial.print(acs712Ampere);
  Serial.println("A");
}


void getPeakRMS() {
  acs712PeakRMS = 0;
  float data[sampleCount];  // 데이터를 저장할 배열
  float peakValue = 0;      // 피크 값 저장
  float rmsValue = 0;       // RMS 값 저장


  // 1000개의 데이터 수집
  for (int i = 0; i < sampleCount; i++) {
    data[i] = analogRead(ACS712_PIN);  // ADC에서 값을 읽음 (예: 전류 센서)
    delayMicroseconds(10);             // 샘플 간 간격
  }
  // 피크 값 찾기
  for (int i = 0; i < sampleCount; i++) {
    if (data[i] > peakValue) {
      peakValue = data[i];  // 더 큰 값이 있으면 피크 값 갱신
    }
  }
  // 피크값으로 RMS값 계산
  rmsValue = peakValue * 0.707;
  acs712PeakRMS = rmsValue / 4095.0 * 3.3;
  Serial.print("피크값 RMS 계산(근사) : ");
  Serial.println(acs712PeakRMS);
}