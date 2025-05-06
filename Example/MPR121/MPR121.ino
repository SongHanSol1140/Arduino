// MPR121의 VCC를 ESP32의 3.3V에 연결합니다.
// MPR121의 GND를 ESP32의 GND에 연결합니다.
// MPR121의 SDA를 ESP32의 GPIO 21에 연결합니다.
// MPR121의 SCL를 ESP32의 GPIO 22에 연결합니다.

#include <Wire.h>
#include <Adafruit_MPR121.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
s
// Adafruit_MPR121 객체 생성
Adafruit_MPR121 cap = Adafruit_MPR121();

// 이전 터치 상태를 저장할 변수
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // 시리얼 포트가 준비될 때까지 대기
    delay(10);
  }

  if (!cap.begin(0x5A)) { // MPR121 초기화, 주소 0x5A 사용
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  
  Serial.println("MPR121 found!");
}

void loop() {
  // 현재 터치된 상태 읽기
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // 각 입력을 반복하면서 상태 확인
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // 상태 업데이트
  lasttouched = currtouched;

  // 잠시 대기
  delay(100);
}
