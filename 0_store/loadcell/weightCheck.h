#ifndef WEIGHT_CHECK_H
#define WEIGHT_CHECK_H

#include "HX711.h"
#include "wifi_mqtt.h"
#include "variables.h"

// 함수 선언
void setZeroFactor(int repeatNumber);
void calculate(int digitalValue);
void checkCalibration(int averageValue);
#endif // WEIGHT_CHECK_H
