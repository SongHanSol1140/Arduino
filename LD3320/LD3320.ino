// LD3320.ino

#include <Arduino.h>
#include <LD3320.h>
VoiceRecognition Voice;  // 음성 인식 객체 선언
void Vioce_INIT();
void Recognize_Voice();

void setup() {
  Serial.begin(115200);
  SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, CS);
  Vioce_INIT(); /* LD3320 음성 인식 초기화 */
}

void loop() {
  Recognize_Voice(); /* LD3320 테스트 */
}

void Vioce_INIT() {
  /********** LD3320 초기화 *****************/
  Voice.init(MIC);               // VoiceRecognition 모듈 초기화
  Voice.addCommand("hello", 0);  // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("ni", 1);     // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("i", 2);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("a", 3);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("e", 4);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("u", 5);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("e", 6);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.addCommand("o", 7);      // 명령 추가, 매개변수(명령 내용, 명령 태그(중복 가능))
  Voice.start();                 // 인식 시작
                                 /*************************************/

  /************* LD3320 디버깅 코드 **************/
  // Voice.reset();
  // readReg(0x6);
  // writeReg(0x35, 0x33);
  // writeReg(0x1b, 0x55);
  // writeReg(0xb3, 0xaa);
  // Serial.print(readReg(0x06));
  // Serial.print(readReg(0x06));
  // Serial.print(readReg(0x35));
  // Voice.addCommand("kai deng", 0);
  // Serial.print(readReg(0xBF));
  // Serial.print("\r\n");
  // delay(2000);
}

void Recognize_Voice() {
  // Serial.println(Voice.read());
  /******************************************/
  switch (Voice.read())  // 인식 결과 판단
  {
    case 0:  // 명령이 "kai deng"인 경우
      Serial.println("000\r\n");
      break;
    case 1:  // 명령이 "guan deng"인 경우
      Serial.println("111\r\n");
      break;
    case 2:
      Serial.println("222\r\n");
      break;
    case 3:
      Serial.println("333\r\n");
      break;
    case 4:
      Serial.println("444\r\n");
      break;
    case 5:
      Serial.println("555\r\n");
      break;
    case 6:
      Serial.println("666\r\n");
      break;
    case 7:
      Serial.println("777\r\n");
      break;
    default:
      // Serial.print("no\r\n");
      break;
  }
  /*****************************************/
}
