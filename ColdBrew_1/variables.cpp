// variables.cpp
#include "variables.h"
// ==============================
//사용 핀
// 온도 입력핀
int tmpCfInputPin = 36;
int tmpCBInputPin = 39;
// 온도 PWM출력핀
int tmpCBPIDPin = 25;
// CT #1, #2, #3
int ctCfPin = 32;
int ctCBPin = 33;
int ctCoolerPin = 35;
// 유량계 입력 핀
int flowMeterPin1 = 23; // #23 순환유량계
int flowMeterPin2 = 22; // #22 유입유량계
// 레벨
int cfLevelPinRX = 16;
int cfLevelPinTX = 17;
int coldbrewLevelPin = 27;
// 압력센서 핀
int coldbrewPressurePin = 21;
int coolerHighPressurePin = 19;
int coolerLowPressurePin = 18;
// ==============================
// MQTT 토픽
char mqttClientName[] = "coldbrewESP32_1";
char mqttUserName[] = "coldbrewESP32_1"; // 유저
char mqttPassword[] = "coldbrewESP32_1"; // 패스워드
char coldBrewSetup[] = "coldbrewMachineSetup";
char coldBrewMachine[] = "coldbrewMachine";
// ==============================
// 온도
// 입력온도
double tmpCfInput = 0.0;
double tmpCBInput = 0.0;
// 출력
double tmpCfOutput = 0.0;
double tmpCBOutput = 0.0;
// 목표온도
double tmpSetCfP = 0.0;
double tmpSetCBP = 0.0;
// 출력제한
double tmpCfOLimit = 0.0;
double tmpCBOLimit = 0.0;
// 온도설정
float tmpCf_CO = 0.0; // 디카페인 설정온도
float tmpBr_EX = 0.0; //브루드 추출온도
float tmpBr_CO = 0.0; // 브루드 냉각온도
float tmpCB_EX = 0.0; //콜드브루 추출온도
float tmpCB_CO = 0.0; // 콜드브루 냉각온도
// ==============================

// CT
float ctCfScale = 0; // 디카페인펌프
float ctCBScale = 0; // 에스프레소 펌프
float ctCoolerScale = 0; // 냉동기 
// 해당 limitScale로 설정된 출력(%단위)을 넘을시 output출력
float ctCfLimit = 0;
float ctCBLimit = 0;
float ctCoolerLimit = 0;
// 읽은 아날로그 출력% 0~3.3v => 0~100%
float ctCfInputPercent= 0.0;
float ctCBInputPercent = 0.0;
float ctCoolerInputPercent = 0.0;
// ==============================

// 유량기
float FlowRate1 = 0; // 2번 유량기 속도
float FlowRate2 = 0; // 1번 유량기 속도
int flowLimit1 = 0; // 송출량 제한
int flowLimit2 = 0; // 송출량 제한
float totalFlow1 = 0; // 1번 유량기에서 나간 액체의 양
float totalFlow2 = 0; // 2번 유량기에서 나간 액체의 양

// ==============================
// Level 초음파 거리측정 센서
int cfLevel = 0;
int coldbrewLevel = 0;
int limitLevel = 100; // 설정값
int limitLevelMin = 200; // 빈 상태 => 값이 높음
int limitLevelMax = 20; // 가득 찬 상태 => 값이 낮음
// ==============================
// 디카페인, 콜드브루 세정횟수
int cfCleanCount = 1;
int cfCleanTime = 60;
int cbCleanCount = 1;
int cbCleanTime = 60;

int timer1 = 60; // 60초
int timer2 = 30; // 30초
int timer3 = 60; //60초
int timer4 = 3600; 
// ==============================
// 압력
float cbPressureInput = 0.0;
float coolerPressureHighInput = 0.0;
float coolerPressureLowInput = 0.0;
float cbPressureLimit = 3.3;
float coolerPressureHighLimit = 3.3;
float coolerPressureLowLimit = 3.3;
// ==============================
boolean heaterStatus = false;
Preferences preferences;
