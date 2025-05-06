#include <HardwareSerial.h>

// RS485 설정
#define RXD2 16
#define TXD2 17

void setup() {
  // 시리얼 통신 설정
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("수신준비 완료");
}

void loop() {
  if (Serial2.available()) {
    // 수신된 데이터를 읽고 출력
    String received = Serial2.readString();
    Serial.print("수신된 메시지: ");
    Serial.println(received);
    Serial2.print("메세지 받았습니다");
  }
}
