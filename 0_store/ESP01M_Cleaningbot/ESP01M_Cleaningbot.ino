/*
    
    IO0 핀과 그옆의 GND선을 하나의 선으로 연결하여 전압을 0V로 만들어야 플래시모드로 부팅되어 코드가 업로드됨
    추가 보드 관리자 URL
    http://arduino.esp8266.com/stable/package_esp8266com_index.json
    보드 선택 - esp 8285 검색 - Generic ESP8285 Module
    ESP-01M에는 USB가 없음 USB TO TTL 컨버터를 사용할것

*/

// main.ino
#include <EEPROM.h>  // 비휘발성 메모리 저장
#include "wifi_mqtt.h"
#include "webPage.h"
#include "irSetup.h"


bool checkStart(int timerset);
bool checkBackHome(int timerset);

void setup() {
  Serial.begin(115200);
  pinMode(checkInPlace, INPUT_PULLUP);
  pinMode(checkInTable, INPUT_PULLUP);
  // IR 발신설정 초기화
  irsend.begin();

  // 와이파이o
  setWifi();
  // MQTT
  setMqtt();
  // 웹서버 초기화
  initWebServer();

  // 비휘발성 메모리 타이머
  timerSetup();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!mqttClient.connected()) {
    setMqtt();
  }

  server.handleClient();
  mqttClient.loop();

  // 청소 시작
  if (cleaningbotRuningState == true) {
    Serial.println("청소시작");
    if (digitalRead(checkInPlace) == HIGH) {  // 청소기가 제자리에서 대기중임을 확인
      Serial.println("테스트1");
      if (digitalRead(checkInTable) == LOW) {  // 청소기가 테이블을 감지했다면 청소신호
        Serial.println("테스트2");
        sendPauseWorkIR();             // 청소 시작명령
        if (!checkStart(timerSet1)) {  // Timer만큼기다리면서 복귀 확인
          Serial.println("테스트3");
          sendPauseWorkIR();
          if (!checkStart(timerSet1)) {
            Serial.println("테스트3");
            sendPauseWorkIR();
            // 에러 발생
            if (!checkStart(timerSet1)) {  // 타이머 대기 재시도
              Serial.println("에러알림1");
              publishMessage("error_01");
              cleaningbotRuningState = false;
              return;
            }
          }
        }

        // checkStart()의 결과가 true라면 (출발했다면) timer2 시간내로 복귀 확인
        if (!checkBackHome(timerSet2) || digitalRead(checkInTable) == LOW) {  // 시간내로 복귀 실패 || 테이블 접근
          sendHomeIR();                                                       // 홈IR 발생
          if (!checkBackHome(timerSet3)) {                                    // 복귀 시도 실패
            Serial.println("청소봇 복귀 실패, 에러 메세지 발신");
            publishMessage("error_02");  // 복귀에러
            cleaningbotRuningState = false;
            return;
          } else {
            // 복귀 완료
            Serial.println("청소봇 복귀 완료, 청소가 끝났습니다.");
            cleaningbotRuningState = false;
            publishMessage("false");
            return;
          }
        }
      }
    }
  }
}

bool checkStart(int timerset) {  // 출발감지
  for (int i = 0; i < (timerset / 100); i++) {
    if (digitalRead(checkInPlace) == LOW) {
      // Serial.println("청소봇 출발 확인");
      delay(100);
      return true;
    } else {
      // WIFI / MQTT 연결 유지
      mqttClient.loop();
      server.handleClient();
      delay(100);
    }
  }
  return false;
}

bool checkBackHome(int timerset) {
  for (int i = 0; i < (timerset / 100); i++) {
    if (digitalRead(checkInPlace) == HIGH) {
      Serial.println("청소봇 복귀 확인");
      cleaningbotRuningState = false;
      publishMessage("false");
      return true;
    } else {
      // WIFI / MQTT 연결 유지
      mqttClient.loop();
      server.handleClient();
      delay(100);
    }
  }
  return false;
}
