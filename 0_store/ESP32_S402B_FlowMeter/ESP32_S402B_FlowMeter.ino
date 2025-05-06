// .ino
#include "wifi_mqtt.h"
#include "variables.h"
#include "flowSensor.h"
// #include "web.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  setWifi();
  // MQTT는 현재 일시 중지
  // setMqtt();


  // 유량계 핀설정
  // pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(FLOW_SENSOR_PIN, INPUT);
  // attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);

  // 모니터링용 웹 서버 시작
  // startWebServer();
  delay(1000);
  Serial.println("유량계 설정 완료");
}


void loop() {
//   if (WiFi.status() != WL_CONNECTED) {
//     setWifi();
//   }
  // MQTT 현재 일시 중지
  // if (!client.connected()) {
  //   setMqtt();
  // }
  // client.loop();
  // 유량 계산
  calculateFlow();

  // 웹 클라이언트 요청 처리
  // handleClientRequests();
}