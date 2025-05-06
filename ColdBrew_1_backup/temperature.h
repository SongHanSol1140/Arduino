#include <Adafruit_MAX31865.h>
#include <PID_v1.h> // PID by Brett Beauregard

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

void initTemperatureControl();
void updateTemperatureControl();

extern Adafruit_MAX31865 thermo1;
extern Adafruit_MAX31865 thermo2;
extern double Kp, Ki, Kd;
extern PID myPID1;
extern PID myPID2;

#endif // TEMPERATURE_H
