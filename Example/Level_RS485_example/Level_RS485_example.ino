#include <HardwareSerial.h>
// https://wiki.dfrobot.com/Laser_Ranging_Sensor_RS485_4m_SKU_SEN0492
// 빨강선 : VCC (5V이상)
// 노란선 : A
// 초록선 : B
// 검은선 : GND
// VCC랑 그라운드를 전력에 같이연결
// RS485 to TTL 컨버터에 A => A / B => B연결 / 초록색이 B 노란색이 A
// 일반적인 TX / RX 와 다르게 RX - RX / TX - TX로 연결해야함
// RS485 설정
#define RXD2 16
#define TXD2 17


uint16_t calculateCRC(uint8_t* data, uint8_t length) {
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
}

void loop() {
  readLevelOrder(0x01);
  answerCheck(0x01);
  // readLevelOrder(0x02);
  // answerCheck(0x02);

  yield();
  delay(1000);
}





void readLevelOrder(uint8_t id) {
  // 보낼 데이터를 배열로 정의
  uint8_t data[] = { id, 0x03, 0x00, 0x34, 0x00, 0x01 };

  // CRC 계산
  uint16_t crc = calculateCRC(data, 6);
  uint8_t crcLow = crc & 0xFF;
  uint8_t crcHigh = (crc >> 8) & 0xFF;

  // CRC 값을 데이터 배열에 추가
  uint8_t message[8] = { id, 0x03, 0x00, 0x34, 0x00, 0x01, crcLow, crcHigh };

  // 데이터를 송신
  Serial2.write(message, sizeof(message));
  delay(10);
}
void answerCheck(uint8_t id) {
  if (Serial2.available() >= 7) {
    uint8_t receivedData[7];
    Serial2.readBytes(receivedData, 7);

    // Serial.print("수신된 메시지: ");
    // for (int i = 0; i < 7; i++) {
    //   if (receivedData[i] < 0x10) {
    //     Serial.print("0");
    //   }
    //   Serial.print(receivedData[i], HEX);
    //   Serial.print(" ");
    // }
    // Serial.println();

    // 수신된 데이터 해석
    if (receivedData[0] == id && receivedData[1] == 0x03) {  // 반환되는 ID가 인자와 같고  받은명령이 0x03(읽기명령)일때
      uint16_t value = ((uint16_t)receivedData[3] << 8) | receivedData[4];
      Serial.print(id);
      Serial.print("에서 수신된 값: ");
      Serial.println(value);
    }
  }
  delay(10);
};