// .ino
#include "wifi_mqtt.h"
#include "variables.h"
void setup() {
  Serial.begin(115200);
  delay(1000);
  setWifi();
  setMqtt();
  // 핀 모드 설정
  pinMode(TELEPHONE_PIN, OUTPUT);  // PIR_PIN을 입력으로 설정
  digitalWrite(TELEPHONE_PIN, HIGH);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  delay(1000);




  Serial.println("출입문 전화기 실행");


  
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!client.connected()) {
    setMqtt();
  }
  client.loop();

  // 요청 처리
  httpServer.handleClient();
  delay(10);
}
