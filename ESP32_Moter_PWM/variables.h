// variables.h
#include <PID_v1.h>

#ifndef VARIABLES_H
#define VARIABLES_H

// ================================================
// 핀변수
extern int ANALOG_PIN;      // 아날로그 VCC 입력 핀
extern int ACS712_PIN;  // 모터 전류 측정핀
extern int SWITCH_PIN;      // 스위치 입력 핀(풀업, GND / GPIO에 연결)
extern int PWM_PIN;         // PWM 출력 핀
// ================================================
// 모터PWM 제어변수

// 목표 Hz(0 ~ 15000);
extern float targetHz;

// 출력제한
extern float limitPwmPercent;
// 주파수 설정
const int pwmFreq = 1500;
const int pwmResolution = 8;
// 버튼 State
extern bool isRunning, currentButtonState, lastButtonState;
// PID설정
extern double Kp, Ki, Kd;
extern double currentPWM, pwmOutput, targetPWM;


extern PID myPID;
// ================================================
// ACS712 Ampere 측정변수
extern float sensitivity;
extern float offsetVoltage;
extern int sampleCount;
extern int R1;
extern int R2;
extern float voltageMultiplier;
extern float acs712Voltage;
extern float acs712Ampere;

#endif  // VARIABLES_H
