#include "level_sensor.h"
#include "variables.h"


HardwareSerial decafLevelSerial(2);

void levelSensorSetup() {
  pinMode(coldbrewLevelPin, INPUT);  // 핀 27을 입력으로 설정
  decafLevelSerial.begin(115200, SERIAL_8N1, 16, 17);
  Serial.println("Level Sensor Setup Complete");
  delay(1000);
}

void updateDecafSensor() {
  if (decafLevelSerial.available()) {
    String inputString = "";
    while (decafLevelSerial.available()) {
      char c = decafLevelSerial.read();
      inputString += c;
    }
    // Serial.println(inputString);

    int index = inputString.indexOf("d:");
    if (index != -1) {
      String distanceString = inputString.substring(index + 2);
      distanceString.trim();
      int distance = distanceString.toInt();
      decafLevel = distance;
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