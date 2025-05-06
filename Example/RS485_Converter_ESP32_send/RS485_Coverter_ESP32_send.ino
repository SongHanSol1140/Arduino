#include <HardwareSerial.h>
// ESP32 TX -> RS485 to TTL Converter TX
// ESP32 RX -> RS485 to TTL Converter RX
// A -> A / B -> B / TX -> TX / RX -> RX
// RS485 설정
#define RXD2 16
#define TXD2 17

void setup() {
  // 시리얼 통신 설정
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  // DE 핀을 HIGH로 설정하여 송신 모드로 전환
  Serial2.print("안녕하세요?");
  Serial.println("메시지를 보냈습니다: 안녕하세요?");
  delay(1000);
   if (Serial2.available()) {
    // 수신된 데이터를 읽고 출력
    String received = Serial2.readString();
    Serial.print("수신된 메시지: ");
    Serial.println(received);
  }
  delay(2000); // 2초 대기
}
