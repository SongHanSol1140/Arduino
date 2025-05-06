
// variables.cpp
#include "variables.h"

// 와이파이
// char wifi_ssid[] = "NNX2-2.4G";
char wifi_ssid[] = "nnx-factory2.4";
// char wifi_password[] = "$@43skshslrtm";
char wifi_password[] = "nanonix817";

// MQTT
char mqttClientName[] = "DoorSystem";
char mqttUserName[] = "nanonix"; // 아이디
char mqttPassword[] = "$@43nanonix"; // 패스워드
char topic[] = "FlowMeterSystem"; // 토픽

// 유량
volatile int pulseCount = 0;
float flowRate = 0.0;
float flowMilliLitres = 0;
float totalMilliLitres = 0.0; 
float nowTime = 0.0;          
unsigned long checkTime = 0;

// 추가 상태 변수
bool isFlowing = false;        // 현재 유량 흐르는 중인지 표시
unsigned long lastPulseTime = 0; // 마지막 펄스 시간
bool wasFlowStopped = true;    // 이전에 흐름이 멈춘 상태였는지 (초기에는 true로 해서 시작시 0세팅)
