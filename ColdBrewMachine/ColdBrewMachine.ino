#include <Wire.h>
#include "variables.h"
#include "wifi_mqtt.h"
#include "MCP23017.h"
#include "PIM517.h"
void setup() {
  Serial.begin(115200);
  setWifi();
  setMqtt();

  Wire.begin(21, 22);
  // MCP23017
  MCP23017_Setup();
  // 온도계 초기화 / CT전압측정
  PIM517_Setup();

  delay(3000);
}

void loop() {
  // Serial.println("=============================================");
  tmpCoffeeCalcurate();
  tmpColdbrewCalcurate();
  tmpHeaterCalcurate();
  // Serial.println("=============================================");
  delay(100);

}
