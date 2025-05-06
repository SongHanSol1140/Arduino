#ifndef VARIABLES_H
#define VARIABLES_H
#include <Preferences.h>
extern char mqttClientName[]; // MQTT접속할 클라이언트 이름
extern char mqttUserName[]; // mqtt유저명
extern char mqttPassword[]; // mqtt패스워드명
extern char coldBrewMachine[];    // 값을 받는 토픽(현재 기기)
extern char coldBrewSetup[]; // => 설정용 토픽
// 온도 감지 핀
extern int tmpCfInputPin;
extern int tmpCBInputPin;
// 온도 PWM출력 핀
extern int tmpCBPIDPin;
// CT : 입력핀
extern int ctCfPin;
extern int ctCBPin;
extern int ctCoolerPin;
// 레벨 감지용 핀
extern int cfLevelPinRX;
extern int cfLevelPinTX;
extern int coldbrewLevelPin;
// 유량계 입력 핀
extern int flowMeterPin1;
extern int flowMeterPin2;
// 압력감지 핀
extern int coldbrewPressurePin;
extern int coolerHighPressurePin;
extern int coolerLowPressurePin;
// ==============================
//  온도계
// 온도 : 입력값
extern double tmpCfInput;
extern double tmpCBInput;
// 온도 : 설정온도
extern double tmpSetCfP;
extern double tmpSetCBP;
// 온도 : 출력제한
extern double tmpCfOLimit; // 출력제한
extern double tmpCBOLimit; // 출력제한
// 온도 : 출력값
extern double tmpCfOutput;
extern double tmpCBOutput;
// ==============================

// 온도 : 설정 온도
// tmpSetCfP / tmpSetCBP에 사용할 변수저장
extern float tmpCf_CO; // 디카페인 설정온도
extern float tmpCB_EX; //콜드브루 추출온도
extern float tmpCB_CO; // 콜드브루 냉각온도
extern float tmpBr_EX; //브루드 추출온도
extern float tmpBr_CO; // 브루드 냉각온도

extern int tmpTolerance;

// CT
// CT 값
extern float ctCfScale;
extern float ctCBScale;
extern float ctCoolerScale;

extern float ctCfLimit;
extern float ctCBLimit;
extern float ctCoolerLimit;
// 읽은 아날로그 출력% 0~3.3v => 0~100%
extern float ctCfInputPercent;
extern float ctCBInputPercent;
extern float ctCoolerInputPercent;

// 유량기
extern float FlowRate1; // 순환유량기
extern float FlowRate2; // 유입유량기
extern int flowLimit1;
extern int flowLimit2;
extern float totalFlow1;
extern float totalFlow2;

// Level 초음파 거리측정 센서
extern int cfLevel;
extern int coldbrewLevel;
extern int limitLevel;
extern int limitLevelMin;
extern int limitLevelMax;

// 디카페인, 콜드브루 세정횟수
extern int cfCleanCount;
extern int cfCleanTime;
extern int cbCleanCount;
extern int cbCleanTime;

// 타이머
extern int timer1;
extern int timer2;
extern int timer3;
extern int timer4;
// ==============================
// 압력
extern float cbPressureInputV;
extern float coolerPressureHighInputV;
extern float coolerPressureLowInputV;
extern float cbPressureLimit;
extern float coolerPressureHighLimit;
extern float coolerPressureLowLimit;
// ==============================
// 히터 PWM 출력여부
extern boolean heaterStatus;
// Preferences 객체
extern Preferences preferences;
#endif // VARIABLES_H
