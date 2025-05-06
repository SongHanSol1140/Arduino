// .ino
#include "wifi_mqtt.h"
#include "variables.h"
void setup() {
  Serial.begin(115200);
  delay(100);
  setWifi();
  setMqtt();
  Serial.println("시스템 Setup");
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!client.connected()) {
    setMqtt();
  }
  client.loop();
  delay(1000);
  Serial.println("작동 확인 메세지");
}
