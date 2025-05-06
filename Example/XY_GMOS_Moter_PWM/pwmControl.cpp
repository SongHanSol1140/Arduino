// pwmControl.h
#include "pwmControl.h"
#include "variables.h"


void softStart() {
  int steps = rampTime / updateInterval;
  float dutyStep = (targetDuty - startDuty) / (float)steps;

  for (int i = 0; i <= steps; i++) {
    currentDuty = startDuty + (dutyStep * i);
    int pwmValue = map(currentDuty, 0, 100, 0, 255);
    ledcWrite(pwmPin, pwmValue);

    Serial.printf("Soft starting: current duty: %.2f%%\n", currentDuty);

    delay(updateInterval);
  }

  currentDuty = targetDuty;
  Serial.println("Soft start completed");
}
