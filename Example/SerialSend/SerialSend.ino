#include <HardwareSerial.h>

// 하드웨어 시리얼 포트 1 사용 (GPIO 16, 17)
HardwareSerial MySerial(1);

void setup() {
  // 기본 시리얼 모니터 시작
  Serial.begin(115200);

  // RS485 통신 시작 (보드레이트 9600, SERIAL_8N1 설정, RX 핀 16, TX 핀 17,)
  MySerial.begin(115200, SERIAL_8N1, 16, 17);

  // 시작 메시지 출력
  Serial.println("RS485 통신 시작");œ
}

void loop() {
  // 보낼 데이터 설정
  String dataToSend = "Hello, RS485!";
  
  // 데이터를 RS485 포트를 통해 전송
  MySerial.println(dataToSend);
  
  // 디버깅을 위해 시리얼 모니터에 전송한 데이터 출력
  Serial.println("Sent: " + dataToSend);
  
  // 1초 대기
  delay(10);
}
