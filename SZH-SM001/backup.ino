// #include <HardwareSerial.h>

// HardwareSerial mySerial(2);  // UART2 사용. 기본 RX = GPIO 16, TX = GPIO 17

// void setup() {
//   Serial.begin(9600);                        // PC와 시리얼 통신 시작
//   mySerial.begin(9600, SERIAL_8N1, 16, 17);  // 음성 모듈과 통신 시작
//   Serial.println("Setup SZH-SM001");

//   delay(2000);

//   // AA 36을 고정된 값으로 한 번에 전송
//   mySerial.write(0xAA);
//   mySerial.write(0x36);

//   Serial.println("Command AA 36 sent.");

//   // 응답 대기 및 처리
//   waitForResponse();

//   delay(2000);

//   // 추가 명령 전송
//   mySerial.write(0xAA);
//   mySerial.write(0x21);
//   waitForResponse();
// }

// void loop() {
//   // loop에서 지속적으로 응답 확인
//   waitForResponse();
// }

// // 음성 인식 모듈의 응답을 대기하고 ASCII, Hex로 출력 및 전체 Hex 문자열로 저장하는 함수
// void waitForResponse() {
//   unsigned long startTime = millis();
//   String asciiResponse = "";  // ASCII 응답을 저장할 문자열
//   String hexResponse = "";    // HEX 응답을 저장할 문자열

//   while (millis() - startTime < 200) {  // 최대 1초간 응답 대기
//     if (mySerial.available()) {
//       char receivedChar = mySerial.read();  // 수신한 데이터 읽기
//       asciiResponse += receivedChar;        // ASCII 문자열로 저장

//       // 전체 응답을 HEX 형식으로 추가
//       if ((byte)receivedChar < 0x10) {
//         hexResponse += "0";  // 16진수 값이 한 자리일 때 앞에 0 추가
//       }
//       hexResponse += String((byte)receivedChar, HEX);  // HEX 문자열로 추가
//     }
//   }

//   // ASCII 응답 결과 출력
//   if (asciiResponse.length() > 0) {
//     Serial.println("\nFull ASCII Response: " + asciiResponse);  // 전체 ASCII 응답 출력
//   }

//   // 전체 HEX 응답 결과 출력
//   if (hexResponse.length() > 0) {
//     Serial.println("Full HEX Response: " + hexResponse);  // 전체 HEX 응답 출력
//   }
// }