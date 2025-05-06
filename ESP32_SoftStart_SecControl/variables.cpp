// variables.cpp
#include "variables.h"

// 핀 설정
int PWM_PIN = 25;        // PWM 출력 핀
int SWITCH_PIN = 18;     // On/Off 스위치 핀 (풀업 저항 연결)

// 소프트 스타트 변수
float targetDutyCycle = 40.0;     // 목표 듀티 사이클 (%)
float minDutyCycle = 30.0;        // 최소 듀티 사이클 (%)
float softStartDuration = 5000.0; // 목표 듀티 사이클에 도달할 때까지 걸리는 시간 (1000 => 1초)
float incrementDelay = 100.0;     // 듀티 사이클 증가 간격 (밀리초)

// PWM 설정
const int PWM_FREQUENCY = 1500;   // PWM 주파수 (Hz)
const int PWM_RESOLUTION = 8;     // PWM 분해능 (비트, 8비트는 0~255)

// 계산용 변수
int steps = 0;                    // 단계 수
float dutyCycleIncrement = 0.0;   // 단계별 듀티 사이클 증가량

// 상태 변수
bool isRunning = false;           // PWM 출력 상태
bool currentButtonState = false;
bool lastButtonState = false;
