// https://www.waveshare.net/study/article-11-1.html
#include "ld3320.h"   // ld3320.h 헤더 파일 포함
VoiceRecognition Vc;  // 음성 인식 클래스 인스턴스

void setup() {
  Serial.begin(115200);
  Serial.println(F("Say keywords.."));
  Vc.init();  // 음성 인식 초기화

  // 키워드와 ID 추가
  Vc.addCommand("xiexie", 0);
  Vc.addCommand("xie", 1);
  Vc.addCommand("a", 2);
  Vc.addCommand("i", 3);
  Vc.addCommand("u", 4);
  Vc.addCommand("e", 5);
  Vc.addCommand("o", 6);
  Vc.addCommand("ari", 7);
  Vc.addCommand("kai", 8);
  Vc.addCommand("tank", 9);
  Vc.addCommand("hong se", 10);
  Vc.start();  // 음성 인식 시작
}

void loop() {
  switch (Vc.read()) {
    case 0:
      Serial.println("0");
      break;
    case 1:
      Serial.println("1");
      break;
    case 2:
      Serial.println("2");
      break;
    case 3:
      Serial.println("3");
      break;
    case 4:
      Serial.println("4");
      break;
    case 5:
      Serial.println("5");
      break;
    case 6:
      Serial.println("6");
      break;
    case 7:
      Serial.println("7");
      break;
    case 8:
      Serial.println("8");
      break;
    default:
      ;
      break;
  }
}
