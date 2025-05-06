#include "level_sensor.h"
#include "variables.h"
// https://www.dfrobot.com/product-2372.html
// 빨강선 : VCC
// 초록선 : RX
// 노란선 : TX
// 검은선 : GND
// 흰색 : 알람

HardwareSerial cfSerial(2);

void levelSensorSetup() {
  pinMode(coldbrewLevelPin, INPUT_PULLUP);  // 핀 27을 입력으로 설정 => 콜드브루 레벨측정 핀
  cfSerial.begin(115200, SERIAL_8N1, cfLevelPinRX, cfLevelPinTX); // 디카페인 레벨측정핀 16 / 17
  Serial.println("Level Sensor Setup Complete");
  delay(1000);
}

void updateCfSensor() {
  if (cfSerial.available()) {
    String inputString = "";
    while (cfSerial.available()) {
      char c = cfSerial.read();
      inputString += c;
    }
    // Serial.println(inputString);

    int index = inputString.indexOf("d:");
    if (index != -1) {
      String distanceString = inputString.substring(index + 2);
      distanceString.trim();
      int distance = distanceString.toInt();
      cfLevel = distance;
    }
  }
}

void updateColdBrewSensor() {
  int coldbrewState = digitalRead(coldbrewLevelPin);  // 핀을 읽음
  if (coldbrewState == HIGH) {
    coldbrewLevel = 1;  // HIGH이면 coldbrewLevel을 1로 설정
  } else {
    coldbrewLevel = 0;  // LOW이면 coldbrewLevel을 0으로 설정
  }
}