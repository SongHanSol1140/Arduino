// main.h
#include <EEPROM.h> // 비휘발성 메모리 저장

#include "webPage.h"
#include "irSetup.h"


const uint16_t checkInPlace = 9;
const uint16_t checkInTable = 10;
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
  setMQTT();
  // 웹서버 초기화
  initWebServer();;

  // 비휘발성 메모리 타이머
  timerSetup();

}

void loop() {
  // 연결 상태 확인
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI 연결 끊김, 재연결 시도");
    reconnectWifi();
  }
  if (!client.connected()) {
    Serial.println("MQTT 연결 끊김, 재연결 시도");
    reconnectMQTT();
  }

  server.handleClient();
  client.loop();

  // 청소 시작
    if(cleaningbotRuningState == true){
        if(digitalRead(checkInPlace) == HIGH){ // 청소기가 제자리에서 대기중임을 확인
            if (digitalRead(checkInTable) == LOW) {  // 청소기가 테이블을 감지했다면 청소신호
                sendPauseWorkIR(); // 청소 시작명령
                if(!checkStart(timerSet1)){  // Timer만큼기다리면서 복귀 확인
                    sendPauseWorkIR();
                    if(!checkStart(timerSet1)){
                        sendPauseWorkIR();
                        // 에러 발생
                        if(!checkStart(timerSet1)){ // 타이머 대기 재시도
                            sendMqttError("error_01");
                            cleaningbotRuningState = false;
                            return;
                        }
                    }                    
                }
  
                // checkStart()의 결과가 true라면 (출발했다면) timer2 시간내로 복귀 확인 
                if(!checkBackHome(timerSet2) || digitalRead(checkInTable) == LOW){ // 시간내로 복귀 실패 || 테이블 접근
                    sendHomeIR(); // 홈IR 발생
                    if(!checkBackHome(timerSet3)){ // 복귀 시도 실패
                        Serial.println("청소봇 복귀 실패, 에러 메세지 발신");
                        sendMqttError("error_02"); // 복귀에러
                        cleaningbotRuningState = false;
                        return;
                    }else{
                        // 복귀 완료
                        Serial.println("청소봇 복귀 완료, 청소가 끝났습니다.");
                        cleaningbotRuningState = false;
                        sendMqttJson(false);
                        return;
                    }
                }
            }
        }
    }
}

bool checkStart(int timerset){ // 출발감지
    for(int i = 0; i < (timerset / 100); i++){
        if(digitalRead(checkInPlace) == LOW){
            // Serial.println("청소봇 출발 확인");
            delay(100);
            return true;
        }else{
            // WIFI / MQTT 연결 유지
            client.loop();
            server.handleClient();
            delay(100);
        }
    }
    return false;
}

bool checkBackHome(int timerset){
    for(int i = 0; i < (timerset / 100); i++){
        if(digitalRead(checkInPlace) == HIGH){
            Serial.println("청소봇 복귀 확인");
            cleaningbotRuningState = false;
            sendMqttJson(false);
            return true;
        }else{
            // WIFI / MQTT 연결 유지
            client.loop();
            server.handleClient();
            delay(100);
        }
    }
    return false;
}
