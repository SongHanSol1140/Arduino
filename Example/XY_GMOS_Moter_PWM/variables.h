// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>

// WiFi 설정
extern const char ssid[];
extern const char password[];

// PWM 설정
extern int pwmFreq;
extern const int pwmPin;
extern const int pwmResolution;

// 버튼 설정
extern const int buttonPin;
extern volatile bool buttonPressed;

// PWM 설정
extern float targetDuty;
extern float startDuty;
extern float currentDuty;

// 소프트 스타트 설정
extern const int rampTime;
extern const int updateInterval;

extern bool pwmRunning;

#endif
