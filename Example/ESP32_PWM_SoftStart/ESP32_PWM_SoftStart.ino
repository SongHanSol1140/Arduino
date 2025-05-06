#include <Arduino.h>

const int CT_CONTROL_PIN = 34;  // 모터 전류 측정 핀
const int noLoadVoltValue = 0;  // 무부하(0A) 시 기본전압 (mV)
const int mvPerAmp = 185;  // 1암페어당 mV (ACS712 기준)
const int numSamples = 1000;  // RMS 계산을 위한 샘플 수

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  delay(1000);
}

void loop() {
  float voltageSum = 0;  // 전압 제곱합
  float currentRMSmA = 0;  // RMS 계산된 전류
  float currentRMSmV = 0;
  float current_mV = 0;
  // numSamples 만큼의 샘플 수집
  for (int i = 0; i < numSamples; i++) {
    int analogValue = analogRead(CT_CONTROL_PIN);  // 아날로그 값 읽기
    current_mV = (analogValue / 4095.0) * 3300;  // mV로 변환 (ESP32 기준)
    float voltageOffset = current_mV - noLoadVoltValue;  // 오프셋 계산
    voltageSum += voltageOffset * voltageOffset;  // 제곱합
    delayMicroseconds(100);  // 샘플 간 딜레이 (적절히 조정 가능)
  }

  // RMS 계산
  Serial.println(current_mV);
  currentRMSmV = sqrt(voltageSum / numSamples);
  currentRMSmA = sqrt(voltageSum / numSamples) / mvPerAmp * 1000;  // mA로 변환

  Serial.print("RMS CurrentRMSmV: ");
  Serial.print(currentRMSmV);
  Serial.println(" mV");
  Serial.print("RMS CurrentRMSmA: ");
  Serial.print(currentRMSmA);
  Serial.println(" mA");

  delay(1000);  // 주기적으로 측정
}
