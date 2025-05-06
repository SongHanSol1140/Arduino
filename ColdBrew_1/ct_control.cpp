#include "ct_control.h"
#include "variables.h"


// PWM 주파수 (Hz) / PWM 해상도 (비트)
const int pwmFreq = 5000;
const int pwmResolution = 8;  // 8비트 0~255 12비트 0~4095

int pwmValue1 = 0;
int pwmValue2 = 0;
int pwmValue3 = 0;

// double adjustedValue = analogValue - (2.5 / 3.3 * 4095.0); // 2.5V에 해당하는 아날로그 값을 뺌


void pwmInputPercent_Cf(int cbPwmValue) {

  ctCfInputPercent = analogRead(ctCfPin) / 4095 * 100;
  Serial.print(ctCfInputPercent);
  Serial.println("%");

  // Serial.print("디카페인 입력값 : ");
  // Serial.print(cbPwmValue);
  // Serial.print(" / ");
  // Serial.print("디카페인 입력전압 : ");
  // Serial.print(ctCfInputPercent);
  // Serial.println("%");
}

void pwmInputPercent_CB(int cbPwmValue) {
  ctCBInputPercent = analogRead(ctCBPin) / 4095 * 100;
  Serial.print(ctCBInputPercent);
  Serial.println("%");
  // Serial.print("콜드브루 입력값 : ");
  // Serial.print(cbPwmValue);
  // Serial.print(" / ");
  // Serial.print("콜드브루 입력전압 : ");
  // Serial.print(ctCBInputPercent);
  // Serial.println("%");
}


void pwmInputPercent_Cooler(int cbPwmValue) {
  ctCoolerInputPercent = analogRead(ctCoolerPin) / 4095 * 100;
  Serial.print(ctCoolerInputPercent);
  Serial.println("%");
  // Serial.print("냉동기 입력값 : ");
  // Serial.print(cbPwmValue);
  // Serial.print(" / ");
  // Serial.print("냉동기 입력전압 : ");
  // Serial.print(ctCoolerInputPercent);
  // Serial.println("%");
}




void ctSetup() {

  pinMode(ctCfPin, INPUT);
  pinMode(ctCBPin, INPUT);
  pinMode(ctCoolerPin, INPUT);
  Serial.println("CT Setup Complete");
}


// 아날로그값 받기
void updateCTControl() {
  pwmInputPercent_Cf();

  pwmInputPercent_CB();

  pwmInputPercent_Cooler();
  delay(100);
}
