// variables.cpp
#include "variables.h";
int hash3 = 4;
int hash5 = 5;
int hash6 = 17;
int hash8 = 18; // 콜드브루 송출
int hash9 = 19;
int hash11 = 23; // 순환 펌프
int hash12 = 12;
int hash13 = 13;
int hash14 = 14; 
int hash15 = 15; // 디카페인 펌프 => 펌프로 물을 돌림
int hash16 = 16;
int hash20 = 33;
int hash21 = 21; // 커피 보틀에 물 빼기
int hash22 = 22; // 커피 보틀에 물 넣기
int hash24 = 27;
int hash25 = 25;
int hash26 = 26;
// 와이파이
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";
// MQTT 토픽명
char mqttClientName[] = "coldbrew_ESP32_2"; // 클라이언트
char mqttUserName[] = "coldbrew_ESP32_2"; // 유저
char mqttPassword[] = "coldbrew_ESP32_2"; // 패스워드
char coldbrewSetup[] = "coldbrewMachineSetup"; // => 설정용 토픽(ESP32_1)
char coldbrewMachine[] = "coldbrewMachine";    // 값을 받는 토픽(현재 기기: ESP32_2)
char middleServer1[] = "middleServer1";    // 커피머신 작동중인지 확인하는 장비서버
char middleServer1_Response[] = "middleServer1_Response";
// 머신 상태
bool systemStatus = true;
bool coffeeMachineStatus = false;
bool emergency = false;

// 현재 머신 프로세스
Process currentProcess = NONE;


// PT100ohm
// 입력온도
double tmpInput1 = 0; // 디카페인 온도
double tmpInput2 = 0; // 콜드브루 온도
double tmpOutput1 = 0; // 디카페인 온도에따른 PWM출력
double tmpOutput2 = 0; // 콜드브루 온도에 따른 PWM출력
double setTmpPoint1 = 35.0; // 디카페인 목표 온도
double setTmpPoint2 = 35.0; // 콜드브루 목표 온도
double tmpOutLimit1 = 100.0; // 디카페인 출력제한
double tmpOutLimit2 = 100.0; // 콜드브루 출력제한
// 냉각기 작동여부
extern bool coolingStatus = false;
// 펌프 작동여부
bool decafCoolingStatus = false;
bool coldbrewCoolingStatus = false;
// CT
// 증폭 스케일 => 올바른 %를 얻기위함
// => 만약 스케일이 120%라면 3.3v시 120%가 출력되는데
// 문제는 40%를 1.32v라고 치면 40%(1.32v) 측정시 40%가 안나옴
int scale1 = 120;
int scale2 = 120;
// 해당 limitScale로 설정된 출력(%단위)을 넘을시 output출력
int limitScale1 = 35;
int limitScale2 = 60;
// 읽은 아날로그 출력% 0~3.3v => 0~100%
int convertedScale1 = 0;
int convertedScale2 = 0;

// 유량기
int flowLimit1 = 200; // 순환량 제한 => 유량기에서 200ml가 순환했다면
int flowLimit2 = 1000; // 유입량 제한 => 유량기에서 1000ml가 들어왔다면
double totalFlow1 = 0; // 순환 유량계에서 나간 양
double totalFlow2 = 0; // 유입 유량계에서 나간 양

// Level 초음파 거리측정 센서
int decafLevel = 0;
int coldbrewLevel = 0;
int pvLevelTolerance = 3;
int limitLevel = 100; // 설정값
int limitLevelMin = 200; // 빈 상태 => 값이 높음
int limitLevelMax = 50; // 가득 찬 상태 => 값이 낮음

// 디카페인, 콜드브루 세정횟수
int decafCleanCount = 2; // 필요한 디카페인 세정 횟수
int decafCleanCurrentCount = 0; // 현재 디카페인 세정 횟수
int decafCleanTime = 60;
int cbCleanCount = 2; // 필요한 콜드브루 세정 횟수
int cbCleanCurrentCount = 0; // 현재 콜드브루 세정 횟수
int cbCleanTime = 60;

int timer1 = 1;
int timer2 = 5;
int timer3 = 10;
int timer4 = 60;

// 버튼 인터럽 => while문 종료용
bool buttonInterrupt = false;

Preferences preferences;
