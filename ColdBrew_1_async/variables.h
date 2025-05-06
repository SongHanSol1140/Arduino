#ifndef VARIABLES_H
#define VARIABLES_H
#include <Preferences.h>
extern char mqttClientName[];   // MQTT접속할 클라이언트 이름(중복불가)
extern char coldBrewMachine[];    // 값을 받는 토픽(현재 기기)
extern char coldBrewSetup[]; // => 설정용 토픽
// 콜드브루 레벨 감지용 핀
extern int coldbrewLevelPin;
// CT사용핀
extern int outputSignal1;
extern int outputSignal2;
extern int inputSignal1;
extern int inputSignal2;
// PT100ohm
extern double tmpInput1;
extern double tmpInput2;
extern double tmpOutput1;
extern double tmpOutput2;
extern double setTmpPoint1;
extern double setTmpPoint2;
extern double tmpOutLimit1;
extern double tmpOutLimit2;
extern int tmpTolerance;
extern bool coolingStatus;;

// CT
extern int scale1;
extern int scale2;
extern int limitScale1;
extern int limitScale2;
extern int convertedScale1;
extern int convertedScale2;

// 유량기
extern double FlowRate1; // 순환유량기
extern double FlowRate2; // 유입유량기
extern int flowLimit1;
extern int flowLimit2;
extern double totalFlow1;
extern double totalFlow2;

// Level 초음파 거리측정 센서
extern int decafLevel;
extern int coldbrewLevel;
extern int limitLevel;
extern int limitLevelMin;
extern int limitLevelMax;

// 디카페인, 콜드브루 세정횟수
extern int decafCleanCount;
extern int decafCleanTime;
extern int cbCleanCount;
extern int cbCleanTime;

// 타이머
extern int timer1;
extern int timer2;
extern int timer3;
extern int timer4;

// Preferences 객체
extern Preferences preferences;
#endif // VARIABLES_H
