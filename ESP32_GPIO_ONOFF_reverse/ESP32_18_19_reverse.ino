#include "variables.h"
static int ButtonState = HIGH;
void setup() {
  Serial.begin(115200);
  pinMode(Switch_Pin, INPUT_PULLUP);
  pinMode(Pin_One, OUTPUT);
  digitalWrite(Pin_One, LOW);
  pinMode(Pin_Two, OUTPUT);
  digitalWrite(Pin_Two, HIGH);
  Serial.println("ESP32 Setup Clear - CheckMessage");
}

void loop() {
  int currState = digitalRead(Switch_Pin);
  if (currState == LOW && ButtonState == HIGH) {
    digitalWrite(Pin_One, !digitalRead(Pin_One));
    digitalWrite(Pin_Two, !digitalRead(Pin_Two));
    Serial.println("Button Pressed - Pin states reversed!");  // 디버깅 메시지 추가
    
  }
  // 버튼 상태 추적
  ButtonState = currState;
  delay(10);
}
