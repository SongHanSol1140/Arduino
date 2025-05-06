// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H
#include <Preferences.h>
#include <string>
// =================================
// 핀 설정
// 전자변
extern int hash1;
extern int hash2;
extern int hash3;
extern int hash4;
extern int hash5; 
extern int hash6;
extern int hash7;
extern int hash8;
extern int hash9;
extern int hash10;
extern int hash11;
extern int hash12;
extern int hash13;
extern int hash14;
extern int hash15;
// 온도 냉동기 ON/OFF PIN
extern int tmpCoolerPin;
// =================================
// 와이파이 & MQTT
// WIFI
extern const char ssid[];
extern const char password[];
// MQTT topic
extern char mqttClientName[];         // MQTT접속할 클라이언트 이름
extern char mqttUserName[]; // mqtt유저명
extern char mqttPassword[]; // mqtt패스워드명
extern char coldbrewMachine[];        // 값을 받는 토픽(현재 기기)
extern char coldbrewSetup[];          // => 설정용 토픽
extern char coldbrewController[];      // => 
extern char middleServer1[];          // 작동중인지 확인하는 장비서버
extern char middleServer1_Response[];  // 서버에게 요청을 응답받는 토픽 => 다른장비들도 여기서받기때문에 응답값에서 분리할수잇도록
// =================================
// Status
extern bool systemStatus;
extern bool coffeeMachineStatus;
extern bool emergency;
extern bool coolerStatus;
extern bool heaterStatus;
// =================================
// Process
// 에러 알림용
// 머신 현재 동작
enum Process1 {
  NONE,
  COFFEE_CLEANING,
  COFFEE_LOWER_CLEANING,
  COFFEE_CYCLE_CLEANING,
  COLD_BREW_CLEANING,
  COLD_BREW_LINE_CLEANING1,
  COLD_BREW_LINE_CLEANING2,
  COFFEE_EXTRACTION,
  COFFEE_COOLING,
  COFFEE_TRANSFER,
  BOTTLE_TRANSFER,
  BREWED_EXTRACTION,
  BREWED_COOLING,
  BREWED_TRANSFER,
  COLD_BREW_EXTRACTION,
  COLD_BREW_COOLING,
  COLD_BREW_TRANSFER
};
extern Process1 currentProcess;
// 현재 운전 프로세스
enum Process2 {
  CLEANING,
  COLDBREW,
  COFFEE
};
extern Process2 switchProcess;
// =================================
// NTC 온도센서
// 온도 : 입력값
extern double tmpCfInput;
extern double tmpCBInput;
// 온도 : 출력값
extern double tmpCfOutput;
extern double tmpCBOutput;
// 온도 : 목표온도
extern double tmpCfSetPoint;
extern double tmpCBSetPoint;
// 온도 : 출력제한
extern double tmpCfOLimit; // 출력제한
extern double tmpCBOLimit; // 출력제한
// 온도 : 설정 온도
// tmpSetCfP / tmpSetCBP에 사용할 변수저장
extern double tmpCf_CO; // 디카페인 설정온도
extern double tmpBr_EX; //브루드 추출온도
extern double tmpBr_CO; // 브루드 냉각온도
extern double tmpCB_EX; //콜드브루 추출온도
extern double tmpCB_CO; // 콜드브루 냉각온도
// =================================
// CT
// CT 스케일
extern double ctCfScale;
extern double ctCBScale;
extern double ctCoolerScale;
// CT 출력제한
extern double ctCfLimit;
extern double ctCBLimit;
extern double ctCoolerLimit;
// CT 입력값
extern double ctCfInputV;
extern double ctCBInputV;
extern double ctCoolerInputV;
// =================================
// 유량기
extern int flowLimit1; // #23
extern int flowLimit2; // #22
extern double totalFlow1;
extern double totalFlow2;
// =================================
// Level 초음파 거리측정 센서
extern int cfLevel; // 디카페인 레벨 센서 구체적인 거리(mm)값
extern int coldbrewLevel; // 콜드브루 on/off여부(감지형 on/off센서)
extern int pvLevelTolerance;
extern int limitLevel;
extern int limitLevelMin;
extern int limitLevelMax;
// =================================
// 각종 변수들
extern int tmpTolerance;
extern std::string errorMessage; 

// 디카페인, 콜드브루 세정횟수
extern int cfCleanCount; // 필요한 디카페인 세정 횟수
extern int cfCleanCurrentCount; // 현재 디카페인 세정 횟수
extern int cfCleanTime;
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
extern bool transferInterrupt;
#endif  // VARIABLES_H
