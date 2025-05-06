#include <WiFi.h>
// 출력
const int dacPin1 = 25;   // 아날로그 1.65V를 출력할 핀
const int dacPin2 = 26;   // 아날로그 3.3V를 출력할 핀
const int pwmPin1 = 32;   // PWM 출력 핀 (듀티 사이클 25%)
const int pwmPin2 = 33;   // PWM 출력 핀 (듀티 사이클 50%)
const int digitalOutPin1 = 35;  // 디지털 출력 핀 (HIGH)
const int digitalOutPin2 = 27;  // 디지털 출력 핀 (LOW)
const int digitalInPin1 = 16;   // 디지털 입력 핀
const int digitalInPin2 = 17;   // 디지털 입력 핀
const int pwmInPin1 = 18;       // PWM 입력 핀
const int pwmInPin2 = 19;       // PWM 입력 핀
const int analogInPin1 = 34;    // 아날로그 입력 핀
const int analogInPin2 = 39;    // 아날로그 입력 핀

void setup() {
  Serial.begin(115200);

  // DAC 설정
  dacWrite(dacPin1, 128);  // 1.65V 출력 (3.3V / 2)
  dacWrite(dacPin2, 255);  // 3.3V 출력 (최대값)

  // PWM 출력 설정
  ledcAttach(pwmPin1, 5000, 8); // 32번 핀 PWM설정
  ledcAttach(pwmPin2, 5000, 8); // 33번 핀 PWM설정
  ledcWrite(32, 25 * 2.55);
  ledcWrite(33, 50 * 2.55);

  // 디지털 출력 설정
  pinMode(digitalOutPin1, OUTPUT);
  pinMode(digitalOutPin2, OUTPUT);
  digitalWrite(digitalOutPin1, HIGH);
  digitalWrite(digitalOutPin2, LOW);

  // 디지털 입력 설정
  pinMode(digitalInPin1, INPUT_PULLUP);
  pinMode(digitalInPin2, INPUT_PULLUP);

  // PWM 입력 설정
  pinMode(pwmInPin1, INPUT);
  pinMode(pwmInPin2, INPUT);

  // 아날로그 입력 설정
  pinMode(analogInPin1, INPUT);
  pinMode(analogInPin2, INPUT);
}

void loop() {
  // 디지털 입력 읽기
  int digitalInState1 = digitalRead(digitalInPin1);
  int digitalInState2 = digitalRead(digitalInPin2);

  // PWM 입력 읽기
  int pwmInValue1 = pulseIn(pwmInPin1, HIGH);
  int pwmInValue2 = pulseIn(pwmInPin2, HIGH);

  // 아날로그 입력 읽기  
  int analogInValue1 = analogRead(analogInPin1);
  int analogInValue2 = analogRead(analogInPin2);

  // 시리얼 모니터에 출력
  Serial.println("디지털 입력 상태:");
  Serial.print("  16번 핀: ");
  Serial.println(digitalInState1 == HIGH ? "HIGH" : "LOW");
  Serial.print("  17번 핀: ");  
  Serial.println(digitalInState2 == HIGH ? "HIGH" : "LOW");

  Serial.println("PWM 입력 값:");
  Serial.print("  18번 핀: ");
  Serial.println(pwmInValue1);
  Serial.print("  19번 핀: ");
  Serial.println(pwmInValue2);

  Serial.println("아날로그 입력 값:");  
  Serial.print("  34번 핀: ");
  Serial.println(analogInValue1);
  Serial.print("  39번 핀: ");
  Serial.println(analogInValue2);

  Serial.println();

  // 1초 대기  
  delay(1000);
}