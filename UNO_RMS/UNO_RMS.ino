const int analogInPin = 34;  // ACS712의 아날로그 출력을 읽는 핀
const float ACS712_sensitivity = 0.100; // ACS712-05B의 감도는 100mV/A
float offsetVoltage = 1.5;  // ACS712의 0A 기준값(측정값에서 이 값만큼 빼서 0으로 만듦)

const int sampleCount = 1000;  // 샘플 수를 1000개로 설정

// 전압 분배기 관련 설정 (10kΩ & 20kΩ 저항)
const float R1 = 10000.0;  // 10kΩ 저항
const float R2 = 20000.0;  // 20kΩ 저항
const float voltageMultiplier = (R1 + R2) / R1;  // 전압 분배 공식

float voltage = 0;  // 전압 RMS 값 저장 변수
float ampere = 0;


// 무부하 상태 오프셋 보정 함수
void calibrateCurrentSensor() {
  long sum = 0;
  for (int i = 0; i < sampleCount; i++) {
    int adcValue = analogRead(analogInPin);  // 전류 센서의 ADC 값 읽기
    sum += adcValue;
    delayMicroseconds(10);
  }
  float averageADC = sum / sampleCount;  // ADC 값의 평균 계산
  offsetVoltage = getVoltage(averageADC);  // 평균 전압을 오프셋 값으로 설정
}

// 기준 전압 계산 (전압 분배기를 통해 계산됨)
float getVoltage(int rawADCValue) {
  float currentVoltage = (rawADCValue / 4095.0) * 3.3;  // 전압 계산
  return currentVoltage * voltageMultiplier;  // 전압 분배기 공식 적용
}

// RMS 전류 계산 함수
void getRMS() {
  float ampSum = 0;
  float voltageSum = 0;
  for (int i = 0; i < sampleCount; i++) {
    int adcValue = analogRead(analogInPin);
    float currntVoltage = getVoltage(adcValue);
    
    // 전압(V) 계산
    voltageSum += currntVoltage * currntVoltage;  // 전압의 제곱을 합산
    
    // 전류(A) 계산 (감도 적용)
    float zeroValue = currntVoltage - offsetVoltage;  // 오프셋 적용
    float current = zeroValue / ACS712_sensitivity;
    ampSum += current * current;  // RMS 계산을 위해 제곱값 합산
    delayMicroseconds(10);  // 샘플 간격 동일하게 설정
  }

  voltage = sqrt(voltageSum / sampleCount);  // 전압의 RMS 값 계산
  ampere = sqrt(ampSum / sampleCount);  // 전류의 RMS 값 계산
}

void setup() {
  Serial.begin(115200);  // 시리얼 통신 초기화
  delay(1000);
  calibrateCurrentSensor();
  Serial.print("보정값 : ");
  Serial.println(offsetVoltage);
  delay(1000);
}

void loop() {
  getRMS();
  Serial.print("V (RMS) : ");
  Serial.print(voltage, 2);
  Serial.print(" / A : ");
  Serial.println(ampere, 2);
  delay(1000);
}
