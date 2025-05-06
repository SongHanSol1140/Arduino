// variables.cpp
#include "variables.h"

// WiFi 설정
extern const char ssid[] = "NNX2-2.4G";
extern const char password[] = "$@43skshslrtm";

// PWM 설정
extern int pwmFreq = 50000;
extern const int pwmPin = 25;
extern const int pwmResolution = 8;

// 버튼 설정
extern const int buttonPin = 17;
extern volatile bool buttonPressed = false;

// PWM 설정
extern float targetDuty = 60.0f;
extern float startDuty = 20.0f;
extern float currentDuty = 0.0f;

// 소프트 스타트 설정
extern const int rampTime = 1000;
extern const int updateInterval = 20;

extern bool pwmRunning = false;
