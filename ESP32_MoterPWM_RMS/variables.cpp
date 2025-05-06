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
// ACS712 CT 변수

float ctLimit = 4.00; // => CT 측정값이 해당값보다 높을시 스위치를 off함

float zeroOffsetVoltage = 0.07; // 무부하시 오차보정
float sensitivity = 0.185;  // 전압 / sensitivity => A
float calibrationFator = 1.15; // 낮게 들어오는 전압값을 보정하기위한 배율값




float offsetVoltage = 0.0; // 오프셋값 => 자동으로 설정됨
int sampleCount = 1000;
int R1 = 10000;
int R2 = 20000;
float voltageMultiplier = (R1 + R2) / R1;
float acs712Ampere = 0;