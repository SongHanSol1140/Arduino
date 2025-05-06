#include <Arduino.h>

// 핀 설정
const int currentSensorPin = 34;  // ESP32의 ADC 핀, 전류 센서의 출력이 연결된 핀
const float vRef = 3.3;           // ESP32의 ADC 기준 전압
const int adcMaxValue = 4095;     // ESP32의 12비트 ADC 해상도

// 전류 센서의 감도 (ACS712 20A 버전: 100mV per A)
const float sensitivity = 0.100;  // 100mV/A

// 전압 분배기 관련 설정 (10kΩ & 20kΩ 저항)
const float R1 = 10000.0;         // 10kΩ 저항
const float R2 = 20000.0;         // 20kΩ 저항
const float voltageMultiplier = (R1 + R2) / R1;  // 전압 분배 공식

// 타이밍 관련 설정
const int numSamples = 500;       // 평균을 낼 샘플 수
const int sampleInterval = 2;     // 샘플 간격(ms)


// 사용자 정의 오프셋 값 (무부하시 1.667V로 설정)
float currentOffset = 1.667;      // 무부하 상태에서 전압 오프셋 설정

// 기준 전압 계산 (전압 분배기를 통해 계산됨)
float getDividedVoltage(float rawADCValue) {
  float voltage = (rawADCValue / adcMaxValue) * vRef;
  return voltage * voltageMultiplier;  // 전압 분배기 공식 적용
}

// 전류 측정 함수 (RMS 방식)
float measureCurrentRMS() {
  float sum = 0;
  
  for (int i = 0; i < numSamples; i++) {
    int adcValue = analogRead(currentSensorPin);  // 전류 센서의 ADC 값 읽기
    float sensorVoltage = getDividedVoltage(adcValue);  // 센서 출력 전압 계산
    float voltageDifference = sensorVoltage - currentOffset;  // 오프셋 적용
    float current = voltageDifference / sensitivity;  // 전류 계산 (감도 적용)
    sum += current * current;  // RMS 계산을 위해 제곱값 합산
    delay(sampleInterval);
  }

  float rmsCurrent = sqrt(sum / numSamples);  // RMS 값 계산
  return rmsCurrent;
}

// 오프셋 보정 함수 (무부하 상태에서 센서 보정)
void calibrateCurrentSensor() {
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    int adcValue = analogRead(currentSensorPin);  // 전류 센서의 ADC 값 읽기
    sum += adcValue;
    delay(sampleInterval);
  }
  float averageADC = sum / numSamples;  // ADC 값의 평균 계산
  currentOffset = getDividedVoltage(averageADC);  // 평균 전압을 오프셋 값으로 설정
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 12비트 ADC 해상도 설정

  // 센서 보정
  calibrateCurrentSensor();
  Serial.print("Calibrated Current Offset: ");
  Serial.println(currentOffset, 3);  // 보정된 오프셋 값 출력
}

void loop() {
  // RMS 전류 측정
  float currentRMS = measureCurrentRMS();
  Serial.print("Measured Current (RMS): ");
  Serial.print(currentRMS, 3);  // 소수점 3자리까지 출력
  Serial.println(" A");

  delay(1000);  // 1초 간격으로 측정
}