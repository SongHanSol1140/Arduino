// #include <Arduino.h>
// #include "LD3320.h"

// VoiceRecognition Voice; // 음성 인식 객체 생성

// void setup() {
//     Serial.begin(115200);
//     SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, CS);

//     // LD3320 초기화
//     Voice.init(MIC); // 초기화 시 MIC 사용

//     // 테스트 코드 시작
//     Voice.reset(); // LD_reset()에 해당하는 기능: LD3320 모듈 리셋

//     writeReg(0x35, 0x33); // 레지스터 0x35에 값 0x33 쓰기
//     writeReg(0x1b, 0x55); // 레지스터 0x1b에 값 0x55 쓰기
//     writeReg(0xb3, 0xaa); // 레지스터 0xb3에 값 0xaa 쓰기

//     // 레지스터 값 읽기
//     Serial.println(readReg(0x35)); // 레지스터 0x35의 값 출력
//     Serial.println(readReg(0x1b)); // 레지스터 0x1b의 값 출력
//     Serial.println(readReg(0xb3)); // 레지스터 0xb3의 값 출력
// }

// void loop() {
//     // 루프에서는 별도로 할 일이 없음
// }
