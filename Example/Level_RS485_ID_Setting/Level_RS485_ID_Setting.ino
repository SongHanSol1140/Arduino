#include <HardwareSerial.h>
// 빨강선 : VCC
// 노란선 : A
// 초록선 : B
// 검은선 : GND
// RS485 설정
#define RXD2 16
#define TXD2 17
// 바꾸기전 ID
uint8_t prevID = 0x50;
// 바꿀 ID
uint8_t nextID = 0x02;

uint16_t calculateCRC(uint8_t *data, uint8_t length) {
  uint16_t crc = 0xFFFF;
  for (uint8_t pos = 0; pos < length; pos++) {
    crc ^= (uint16_t)data[pos];
    for (uint8_t i = 8; i != 0; i--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
  
}
void setup() {
  // 시리얼 통신 설정
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  // 보낼 데이터를 배열로 정의
  uint8_t data[] = { prevID, 0x06, 0x00, 0x1a, 0x00, nextID };
  // data[5] => 변경할 ID
  uint16_t crc = calculateCRC(data, 6);
  uint8_t message[8];
  memcpy(message, data, 6);
  message[6] = crc & 0xFF;
  message[7] = (crc >> 8) & 0xFF;


  // 데이터를 송신
  Serial2.write(message, sizeof(message));
  Serial.println("메시지를 보냈습니다: ID 설정");

  delay(10);
  if (Serial2.available() >= 7) {
    uint8_t receivedData[7];
    Serial2.readBytes(receivedData, 7);

    Serial.print("수신된 메시지: ");
    for (int i = 0; i < 7; i++) {
      if (receivedData[i] < 0x10) {
        Serial.print("0");
      }
      Serial.print(receivedData[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // 수신된 데이터 해석
    if (receivedData[0] == nextID) { // 반환되는 ID가 50(기본값)이고 받은명령이 0x03(읽기명령)일때
      uint16_t value = ((uint16_t)receivedData[3] << 8) | receivedData[4];
      Serial.print("수신된 값: ");
      Serial.println(value);
    }
  }
  
}


void loop() {

}
