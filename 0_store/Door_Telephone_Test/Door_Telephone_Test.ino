// .ino
#include "wifi_mqtt.h"
#include "variables.h"
void setup() {
  Serial.begin(115200);
  delay(1000);
  setWifi();
  // setMqtt();
  // 핀 모드 설정
  pinMode(TELEPHONE_PIN1, OUTPUT);  // PIR_PIN을 입력으로 설정
  digitalWrite(TELEPHONE_PIN1, HIGH);
  pinMode(TELEPHONE_PIN2, OUTPUT);
  digitalWrite(TELEPHONE_PIN2, LOW);
  delay(1000);

  // UART통신 받기
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("출입문 전화기 실행");


  
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  // if (!client.connected()) {
  //   setMqtt();
  // }
  // client.loop();

  // UART
  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    Serial.print("Received from Pi: ");
    Serial.println(msg);

    // Example: toggle phone on "cancleCall"
    if (msg.startsWith("cancelCall")) {
      Serial.println("작동확인");
      digitalWrite(TELEPHONE_PIN1, LOW);
      delay(500);
      digitalWrite(TELEPHONE_PIN1, HIGH);
    }
  }
  delay(10);
}
