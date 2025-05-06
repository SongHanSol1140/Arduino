#ifndef VARIABLES_H
#define VARIABLES_H
#include <Preferences.h>
// 핀 설정
// 핀 설정
extern int hash3;
extern int hash5;
extern int hash6;
extern int hash8;
extern int hash9; 
extern int hash11;
extern int hash12;
extern int hash13;
extern int hash14;
extern int hash15;
extern int hash16;
extern int hash20;
extern int hash21;
extern int hash22;
extern int hash24;
extern int hash25;
extern int hash26;
// WIFI
extern const char ssid[];
extern const char password[];
// MQTT topic
extern char mqttClientName[];         // MQTT접속할 클라이언트 이름
extern char mqttUserName[]; // mqtt유저명
extern char mqttPassword[]; // mqtt패스워드명
extern char coldbrewMachine[];        // 값을 받는 토픽(현재 기기)
extern char coldbrewSetup[];          // => 설정용 토픽
extern char middleServer1[];          // 작동중인지 확인하는 장비서버
extern char middleServer1_Response[];  // 서버에게 요청을 응답받는 토픽 => 다른장비들도 여기서받기때문에 응답값에서 분리할수잇도록
// 머신 상태
extern bool systemStatus;
extern bool coffeeMachineStatus;
extern bool emergency;
extern bool coolingStatus;
// 머신 현재 동작
enum Process {
  NONE,
  COFFEE_CLEANING,
  COFFEE_LOWER_CLEANING,
  DECAF_CYCLE_CLEANING,
  COLD_BREW_CLEANING,
  COLD_BREW_LINE_CLEANING1,
  COLD_BREW_LINE_CLEANING2,
  DECAF_EXTRACTION,
  DECAF_COOLING,
  DECAF_TRANSFER,
  DECAF_TRANSFER_FROM_FRIDGE,
  BREWED_EXTRACTION,
  BREWED_COOLING,
  BREWED_TRANSFER,
  COLD_BREW_EXTRACTION,
  COLD_BREW_COOLING,
  COLD_BREW_TRANSFER
};
extern Process currentProcess;

// PT100ohm
extern double tmpInput1;
extern double tmpInput2;
extern double tmpOutput1;
extern double tmpOutput2;
extern double setTmpPoint1;
extern double setTmpPoint2;
extern double tmpOutLimit1;
extern double tmpOutLimit2;
// 펌프 작동여부(수동 작동여부 컨트롤 + Status true상태 + 목표온도 +tmpTolerance)
extern bool decafCoolingStatus;
extern bool coldbrewCoolingStatus;

// CT
extern int scale1;
extern int scale2;
extern int limitScale1;
extern int limitScale2;
extern int convertedScale1;
extern int convertedScale2;
// 유량기
extern int flowLimit1;
extern int flowLimit2;
extern double totalFlow1;
extern double totalFlow2;

// Level 초음파 거리측정 센서
extern int decafLevel; // 디카페인 레벨 센서 구체적인 거리(mm)값
extern int coldbrewLevel; // 콜드브루 on/off여부(감지형 on/off센서)
extern int pvLevelTolerance;
extern int limitLevel;
extern int limitLevelMin;
extern int limitLevelMax;

// 디카페인, 콜드브루 세정횟수
extern int decafCleanCount; // 필요한 디카페인 세정 횟수
extern int decafCleanCurrentCount; // 현재 디카페인 세정 횟수
extern int decafCleanTime;
extern int cbCleanCount; // 필요한 콜드브루 세정 횟수
extern int cbCleanCurrentCount; // 현재 콜드브루 세정 횟수
extern int cbCleanTime;

// 타이머
extern int timer1;
extern int timer2;
extern int timer3;
extern int timer4;

// Preferences 객체
extern Preferences preferences;


// 버튼 인터럽체크
extern bool buttonInterrupt;
#endif  // VARIABLES_H
