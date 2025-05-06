// https://www.dfrobot.com/product-2372.html
// 빨강선 : VCC
// 노란선 : TX
// 초록선 : RX
// 검은선 : GND
// 흰색 : 알람
#include "level_sensor.h"
void setup() {
  Serial.begin(115200);
  levelSensorSetup();
}

void loop() {
  updateCfSensor();
  delay(100); // 데이터 읽기 주기 설정
}

