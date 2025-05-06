// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>

// 핀 설정
extern int PWM_PIN;        // PWM 출력 핀
extern int SWITCH_PIN;     // On/Off 스위치 핀

// 소프트 스타트 변수
extern float targetDutyCycle;     // 목표 듀티 사이클 (0.0 ~ 100.0)
extern float minDutyCycle;        // 최소 듀티 사이클 (0.0 ~ 100.0)
extern float softStartDuration;   // 목표 듀티 사이클에 도달할 때까지 걸리는 시간 (밀리초)
extern float incrementDelay;      // 듀티 사이클 증가 간격 (밀리초)

// 계산된 변수
extern int steps;                 // 목표 듀티 사이클에 도달하기 위한 단계 수
extern float dutyCycleIncrement;  // 단계별 듀티 사이클 증가량

// 상태 변수
extern bool isRunning;            // PWM 출력 상태
extern bool currentButtonState;
extern bool lastButtonState;

// PWM 설정
extern const int PWM_FREQUENCY;   // PWM 주파수 (Hz)
extern const int PWM_RESOLUTION;  // PWM 분해능 (비트)

#endif
