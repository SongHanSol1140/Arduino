1A = 1.05
2A = 1.93
3A = 2.7;
4A = 3.43
5.6A = 4.34

const int analogPin = 34;  // ACS712 아날로그 핀 연결 (ESP32의 아날로그 입력 핀)
const float sensitivity = 0.185;  // ACS712 20A 모델의 감도 (100mV/A)
const float voltageReference = 3.3;  // ESP32의 ADC 참조 전압
const int adcResolution = 4095;  // ESP32 ADC 해상도 (12-bit)
const int sampleWindow = 1000;  // 샘플링 시간 창(1초)

// 센서에서 오프셋 전압을 직접 측정하여 무부하시의 오프셋 전압을 정확하게 적용
float sensorZero = 0;  // 무부하시 전압을 저장할 변수

// 보정 상수
const float zeroCurrentOffset = 0.07;  // 무부하에서 측정된 전류를 보정하기 위한 상수
const float currentCorrectionFactor = 1.15;  // 실제 부하 전류와 측정된 전류의 차이를 보정하기 위한 상수

float readCurrentRMS(int pin);
void calibrateSensor(int pin);

void setup() {
  Serial.begin(115200);  // 시리얼 모니터 시작
  calibrateSensor(analogPin);  // 센서 오프셋 보정
}

void loop() {
  float currentRMS = readCurrentRMS(analogPin);  // RMS 전류 계산
  currentRMS = currentRMS - zeroCurrentOffset;  // 무부하 보정 상수 적용
  currentRMS = currentRMS * currentCorrectionFactor;  // 측정된 전류 값 보정

  if (currentRMS < 0) {
    currentRMS = 0;  // 0 이하의 값은 0으로 처리
  }

  Serial.print("Current (A): ");
  Serial.println(currentRMS);  // 측정된 전류 출력
  delay(1000);  // 1초 대기
}

// 무부하 상태에서 센서의 오프셋 전압을 측정하는 함수
void calibrateSensor(int pin) {
  long voltageSum = 0;
  int samples = 500;  // 무부하시 오프셋 보정을 위해 500개의 샘플을 사용
  for (int i = 0; i < samples; i++) {
    int sensorValue = analogRead(pin);
    voltageSum += sensorValue;
    delay(1);
  }
  sensorZero = (float)voltageSum / samples * (voltageReference / adcResolution);  // 평균 전압 계산
  Serial.print("Calibrated sensor zero voltage: ");
  Serial.println(sensorZero, 3);
}

// RMS 전류를 측정하는 함수
float readCurrentRMS(int pin) {
  unsigned long startMillis = millis();  // 측정을 시작한 시간
  float currentSquaredSum = 0;  // 전류 제곱의 합
  int sampleCount = 0;  // 샘플 개수

  while (millis() - startMillis < sampleWindow) {
    int sensorValue = analogRead(pin);  // 아날로그 값 읽기
    float voltage = sensorValue * (voltageReference / adcResolution);  // 아날로그 값을 전압으로 변환
    float current = (voltage - sensorZero) / sensitivity;  // 전류 계산 (오프셋 적용)
    currentSquaredSum += current * current;  // 전류의 제곱을 합산
    sampleCount++;  // 샘플 개수 증가
  }

  // RMS 계산: 제곱된 전류의 평균을 구하고, 그 값의 제곱근을 구함
  float currentRMS = sqrt(currentSquaredSum / sampleCount);

  return currentRMS;  // RMS 전류 반환
}
