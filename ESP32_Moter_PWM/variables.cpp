// variables.cpp
#include "variables.h"
// ======================================================================
// 핀설정
int ANALOG_PIN = 25;      // 모터 압력 측정핀
int PWM_PIN = 26;         // PWM 출력 핀
int ACS712_PIN = 34;  // ACS712 모터 전류 측정핀
int SWITCH_PIN = 18;      // 스위치 입력 핀(풀업, GND / GPIO에 연결)
// ======================================================================
// 모터압력 PWM 제어변수

// 목표 Hz(0 ~ 15000);
float targetHz = 12000;

// 출력제한 %
float limitPwmPercent = 80.0;


// 버튼 State
bool isRunning = true;  // PWM 입력 스위치 상태
bool currentButtonState = false;
bool lastButtonState = true;

// PID설정
double currentPWM = 0, pwmOutput = 0, targetPWM = 0;
double Kp = 0.5, Ki = 0.01, Kd = 0.02;
PID myPID(&currentPWM, &pwmOutput, &targetPWM, Kp, Ki, Kd, DIRECT);
// ======================================================================
// ACS712 Ampere 측정변수
float sensitivity = 0.100;
float offsetVoltage = 1.5;
int sampleCount = 1000;;
int R1 = 10000;
int R2 = 20000;
float voltageMultiplier = (R1 + R2) / R1;
float acs712Voltage = 0;
float acs712Ampere = 0;