// #include <HardwareSerial.h>
// // Delete Group 1 - 0xAA01
// // Delete Group 2 - 0xAA02
// // Delete Group 3 - 0xAA03
// // Delete All Groups - 0xAA04
// // Record Group 1 - 0xAA11
// // Record Group 2 - 0xAA12
// // Record Group 3 - 0xAA13
// // Import Group 1 - 0xAA21
// // Import Group 2 - 0xAA22
// // Import Group 3 - 0xAA23
// // Switch Common Mode - 0xAA36
// // Switch Compact Mode - 0xAA37

// HardwareSerial mySerial(2);  // UART2 사용. 기본 RX = GPIO 16, TX = GPIO 17

// void setup() {

//   Serial.begin(9600);                        // PC와 시리얼 통신 시작
//   mySerial.begin(9600, SERIAL_8N1, 16, 17);  // 음성 모듈과 통신 시작
//   delay(1000);
//   Serial.println("명령어를 입력하세요 (예: 'AA 36'):");
// }

// void loop() {
//   // 시리얼 모니터에서 입력받아 명령어를 전송
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');  // 한 줄 입력받기
//     input.trim();                                 // 공백 제거

//     // Common Mode
//     if (input.equalsIgnoreCase("AA 36")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x36);
//       Serial.println("Common Mode: 0xAA 0x36");
//       // Compact Mode
//     } else if (input.equalsIgnoreCase("AA 37")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x37);
//       Serial.println("Compact Mode: 0xAA 0x37");
//       // Group1 삭제
//     } else if (input.equalsIgnoreCase("AA 01")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x01);
//       Serial.println("Group1 삭제: 0xAA 0x01");
//       // Group2 삭제
//     } else if (input.equalsIgnoreCase("AA 02")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x02);
//       Serial.println("Group2 삭제: 0xAA 0x02");
//       // Group3 삭제
//     } else if (input.equalsIgnoreCase("AA 03")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x03);
//       Serial.println("Group3 삭제: 0xAA 0x03");
//       // Group1 녹음
//     } else if (input.equalsIgnoreCase("AA 11")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x11);
//       Serial.println("Group1 녹음: 0xAA 0x11");
//       // Group2 녹음
//     } else if (input.equalsIgnoreCase("AA 12")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x12);
//       Serial.println("Group2 녹음: 0xAA 0x12");
//       // Group3 녹음
//     } else if (input.equalsIgnoreCase("AA 13")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x13);
//       Serial.println("Group3 녹음: 0xAA 0x13");
//       // Group1 음성인식 시작
//     } else if (input.equalsIgnoreCase("AA 21")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x21);
//       Serial.println("Group1 음성인식 시작: 0xAA 0x21");
//       // Group2 음성인식 시작
//     } else if (input.equalsIgnoreCase("AA 22")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x22);
//       Serial.println("Group2 음성인식 시작: 0xAA 0x22");
//       // Group3 음성인식 시작
//     } else if (input.equalsIgnoreCase("AA 23")) {
//       mySerial.write(0xAA);
//       mySerial.write(0x23);
//       Serial.println("Group3 음성인식 시작: 0xAA 0x23");
//     } else {
//       Serial.println("명령어를 확인해주세요.");
//       return;  // 잘못된 명령어일 경우 waitForResponse()를 호출하지 않도록 함
//     }

//     // 명령어가 유효할 경우에만 응답을 대기
//     waitForResponse();
//   }
//   waitForResponse();
// }


// // 음성 인식 모듈의 응답을 대기하고 ASCII, Hex로 출력하는 함수
// void waitForResponse() {
//   unsigned long startTime = millis();
//   String asciiResponse = "";  // ASCII 응답을 저장할 문자열
//   String hexResponse = "";    // HEX 응답을 저장할 문자열

//   while (millis() - startTime < 500) {  // 최대 500ms 동안 응답 대기
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
