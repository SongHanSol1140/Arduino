#include <Arduino.h>

const int pin16 = 16;  // 읽을 핀 번호 (GPIO16)
const int pin17 = 17;  // 읽을 핀 번호 (GPIO17)

void setup() {
  Serial.begin(115200);
  // 내부 풀업 저항 사용
  pinMode(pin16, INPUT_PULLUP);
  pinMode(pin17, INPUT_PULLUP);
  Serial.println("시리얼 모니터에 GPIO16/17 상태를 출력합니다.");
}

void loop() {
  // 핀 상태 읽기
  int state16 = digitalRead(pin16);
  int state17 = digitalRead(pin17);

  // LOW는 ON, HIGH는 OFF로 간주
  Serial.print("Pin 16: ");
  Serial.println(state16 == LOW ? "ON" : "OFF");
  
  Serial.print("Pin 17: ");
  Serial.println(state17 == LOW ? "ON" : "OFF");
  
  Serial.println("-----------------------");
  delay(500);  // 0.5초 대기
}
