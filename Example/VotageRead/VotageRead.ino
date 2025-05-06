#include <Arduino.h>

// 입력 핀 번호
const int inputPin1 = 16;
const int inputPin2 = 17;

// 출력 핀 번호
const int outputPin1 = 18;
const int outputPin2 = 19;

void setup() {
  // 시리얼 통신 시작
  Serial.begin(115200);

  // 입력 핀 설정
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);

  // 출력 핀 설정
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);

  // 출력 핀 초기화
  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, LOW);
}

void loop() {
  // 입력 핀 상태 읽기
  int state1 = digitalRead(inputPin1);
  int state2 = digitalRead(inputPin2);

  // 입력 핀 상태 출력
  Serial.print("Pin 16: ");
  Serial.println(state1 == HIGH ? "HIGH" : "LOW");
  Serial.print("Pin 17: ");
  Serial.println(state2 == HIGH ? "HIGH" : "LOW");

  // 출력 핀 설정
  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, LOW);

  delay(1000);
}
