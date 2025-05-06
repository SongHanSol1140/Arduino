// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>  // String과 millis, delay 함수를 사용하기 위해 추가
extern unsigned long previousMillis;
String Split(String data, char separator, int index);
void printMemoryUsage();
void TimerCheck(int Timer);;
void CoolingControl(double currentTemp, double targetTemp);
void CirculatingFlowMeterCheck();
void InflowFlowMeterCheck();
void WaitCfHeating();
void WaitCfCooling();
void WaitBrewedHeating();
void WaitBrewedCooling();
void WaitColdbrewHeating();
void WaitColdbrewCooling();
void checkMqttValue();
void getCoffeeMachineStatus();
#endif // UTILS_H
