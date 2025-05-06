// main.ino
#include "webPage.h"
#include <EEPROM.h>

void setup() {
    if (!WiFi.config(ip, gateway, subnet)) {
        Serial.println("STA Failed to configure");
    }
    Serial.begin(115200); // 시리얼 통신 초기화(실행), 전송속도 설정;
    setWifi();
    setMQTT();
    initWebServer();


    EEPROM.begin(32); // EEPROM 시작
    tolerance = EEPROM.readInt(0);
    // EEPROM이 초기화되지 않았다면 기본값 설정
    if (tolerance == 0xFFFF) {
        tolerance = 200; // 기본값
    }
    
    // 함수 포인터 전달
    setZeroFactorCallback(setZeroFactor);

    delay(1000);
    setZeroFactor(20);
}


void loop() {
  // 웹서버 & MQTT
  server.handleClient(); // 웹서버
  client.loop(); // => MQTT
  // mqtt / wifi 체크 & 재접속
  reconnectWifi();
  reconnectMQTT();

  // 이동평균 배열에 값 추가
  addArray();
  // 받아온 이동평균 배열로 무게 계산 & mqtt보내기
  if (numElements == averageSize) {
    getAverage();
    checkCalibration(average);
    calculate();
  }
}
