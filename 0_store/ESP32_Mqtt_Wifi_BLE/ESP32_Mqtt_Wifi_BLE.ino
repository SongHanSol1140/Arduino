// .ino
// Peripheral => 주변기기, 주체(Central)기기들이 값을 읽어감
#include "wifi_mqtt.h"
#include "variables.h"
#include "ESP32_BLE.h"
void setup() {
  Serial.begin(115200);
  delay(100);
  setWifi();
  setMqtt();
  setBLE();
  Serial.println("System Setup Complte");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!mqttClient.connected()) {
    setMqtt();
  }
  mqttClient.loop();
  delay(10);
}
