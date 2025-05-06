// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>  // String과 millis, delay 함수를 사용하기 위해 추가
extern unsigned long previousMillis;
String Split(String data, char separator, int index);
void printMemoryUsage();
void TimerCheck(int Timer);;
void CoolingControl(bool trueFalse);
void CirculatingFlowMeterCheck();
void InflowFlowMeterCheck();
void WaitDeacfHeating();
void WaitDecafCooling();
void WaitColdbrewHeating();
void WaitColdbrewCooling();
void checkMqttValue();
void getCoffeeMachineStatus();
#endif // UTILS_H
