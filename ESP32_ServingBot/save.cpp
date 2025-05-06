// #include <HardwareSerial.h>

// // UART1: RX=GPIO16, TX=GPIO17
// // UART2: RX=GPIO18, TX=GPIO19
// HardwareSerial Serial1UART(1);
// HardwareSerial Serial2UART(2);

// const uint32_t BAUD_RATE = 115200;
// const uint16_t PACKET_TIMEOUT_MS = 5;  // 패킷 구분용 타임아웃

// // 패킷 버퍼 크기
// const size_t BUF_SIZE = 256;
// uint8_t buf1[BUF_SIZE];
// uint8_t buf2[BUF_SIZE];
// size_t idx1 = 0, idx2 = 0;
// unsigned long lastTime1 = 0, lastTime2 = 0;

// void setup() {
//   Serial.begin(115200);  // 디버깅용 시리얼 모니터

//   Serial1UART.begin(BAUD_RATE, SERIAL_8N1, 16, 17);
//   Serial2UART.begin(BAUD_RATE, SERIAL_8N1, 18, 19);
// }

// void loop() {
//   unsigned long now = millis();

//   // UART1에서 들어오는 바이트 읽기
//   while (Serial1UART.available()) {
//     if (idx1 < BUF_SIZE) {
//       buf1[idx1++] = Serial1UART.read();
//       lastTime1 = now;
//     } else {
//       // 버퍼 오버플로우 방지
//       Serial1UART.read();
//     }
//   }

//   // UART2에서 들어오는 바이트 읽기
//   while (Serial2UART.available()) {
//     if (idx2 < BUF_SIZE) {
//       buf2[idx2++] = Serial2UART.read();
//       lastTime2 = now;
//     } else {
//       Serial2UART.read();
//     }
//   }

//   // 처리할 패킷 결정: 두 채널 모두 패킷 대기 중이면 먼저 도착한 쪽(timestamp이 더 작은 쪽) 처리
//   bool pkt1Ready = (idx1 > 0) && (now - lastTime1 > PACKET_TIMEOUT_MS);
//   bool pkt2Ready = (idx2 > 0) && (now - lastTime2 > PACKET_TIMEOUT_MS);

//   if (pkt1Ready && (!pkt2Ready || lastTime1 < lastTime2)) {
//     forwardPacket(buf1, idx1, Serial1UART, Serial2UART);
//     idx1 = 0;
//   }
//   else if (pkt2Ready) {
//     forwardPacket(buf2, idx2, Serial2UART, Serial1UART);
//     idx2 = 0;
//   }
// }

// // buf: 패킷 데이터, len: 길이
// // from → to 로 전송하고, Serial(모니터)에 HEX로 한 줄 출력
// void forwardPacket(uint8_t* buf, size_t len, HardwareSerial& from, HardwareSerial& to) {
//   // 시리얼 모니터에 HEX 출력
//   for (size_t i = 0; i < len; i++) {
//     if (buf[i] < 0x10) Serial.print('0');  // 두 자리로 맞추기
//     Serial.print(buf[i], HEX);
//     Serial.print(' ');
//   }
//   Serial.println();

//   // 반대쪽 UART로 한 번에 전송
//   to.write(buf, len);
// }