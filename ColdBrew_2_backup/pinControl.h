// pinControl.h
#ifndef PINCONTROL_H
#define PINCONTROL_H

#include <Arduino.h>

void setupPins();
void controlPin(int pin, bool state);

#endif // PINCONTROL_H