// temperature.h
#include <PID_v1.h> // PID by Brett Beauregard

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

void temperatureSetup();
void updateTemperatureControl();

extern double Kp, Ki, Kd;
extern PID myPID1;
extern PID myPID2;

#endif // TEMPERATURE_H
