// .ino
#include "variables.h"
#include "functions.h"

void setup() {
  Serial.begin(115200);
  setupESP32();
}

void loop() {
  switchControl();
  softStartPWM();
}
