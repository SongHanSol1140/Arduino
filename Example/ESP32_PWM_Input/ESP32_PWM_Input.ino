#include <Arduino.h>

// PWM 입력 핀 번호
const int pwmPin = 32;
const int dacPin1 = 25;  // 1.65V를 출력할 핀
const int dacPin2 = 26;  // 3.3V를 출력할 핀
// PWM 주파수 (Hz)
const int pwmFreq = 1500;

// PWM 해상도 (비트)
const int pwmResolution = 8;

void setup() {
  Serial.begin(115200);
  // DAC 설정
  dacWrite(dacPin1, 127);  // 1.65V 출력 (3.3V / 2)
  dacWrite(dacPin2, 255);  // 3.3V 출력 (최대값)
  // PWM 입력 핀 설정
  pinMode(pwmPin, INPUT);
}

void loop() {
  // PWM 듀티 사이클 읽기
  int dutyCycle = pulseIn(pwmPin, HIGH);
  // PWM 주기 계산
  int period = 1000000 / pwmFreq;
  // 듀티 사이클 백분율 계산
  float dutyCyclePercent = (float)dutyCycle / period;
  // Serial.println(dutyCyclePercent);
  if (dutyCyclePercent == 0) {
    dutyCyclePercent = digitalRead(pwmPin) == HIGH ? 100.00 : 0.00;
  }

  // 결과 출력
  Serial.print("Duty Cycle: ");
  Serial.print(dutyCyclePercent * 100);
  Serial.println("%");
  dacWrite(dacPin2, dutyCyclePercent * 255);
  delay(20);







  // dacWrite(dacPin1, 120);
  // delay(500);
  // dacWrite(dacPin1, 130);
  // delay(500);
  // dacWrite(dacPin1, 140);
  // delay(500);
}