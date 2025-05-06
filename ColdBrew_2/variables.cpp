// variables.cpp
#include "variables.h"

int hash1 = 2;
int hash2 = 4;
int hash3 = 16; 
int hash4 = 17;
int hash5 = 18;
int hash6 = 19;
int hash7 = 21;
int hash8 = 22;
int hash9 = 23;
int hash10 = 13;
int hash11 = 14; 
int hash12 = 27; 
int hash13 = 26;
int hash14 = 25; // 콜드브루 펌프
int hash15 = 33; // 디카페인 펌프
// 온도 냉동기 ON/OFF
int tmpCoolerPin = 32;
int tmpTolerance = 2;
// 와이파이
const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";
// MQTT 토픽명
char mqttClientName[] = "coldbrewESP32_2"; // 클라이언트
char mqttUserName[] = "coldbrewESP32_2"; // 유저
char mqttPassword[] = "coldbrewESP32_2"; // 패스워드
char coldbrewSetup[] = "coldbrewMachineSetup"; // => 설정용 토픽(ESP32_1)
char coldbrewMachine[] = "coldbrewMachine";    // 값을 받는 토픽(현재 기기: ESP32_2)
char coldbrewController[] = "coldbrewController";    // 값을 받는 토픽(현재 기기: ESP32_2)
char middleServer1[] = "middleServer1";    // 커피머신 작동중인지 확인하는 장비서버
char middleServer1_Response[] = "middleServer1_Response";
// 에러 알림용 변수
std::string errorMessage;
// 머신 상태
bool systemStatus = true;
bool coffeeMachineStatus = false;
bool emergency = false;
// 현재 머신 프로세스
Process1 currentProcess = NONE;
Process2 switchProcess = CLEANING;


// NTC
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
double tmpCf_CO = 0.0; // 디카페인 설정온도
double tmpBr_EX = 0.0; //브루드 추출온도
double tmpBr_CO = 0.0; // 브루드 냉각온도
double tmpCB_EX = 0.0; //콜드브루 추출온도
double tmpCB_CO = 0.0; // 콜드브루 냉각온도






// CT
// CT 스케일
double ctCfScale = 0.0; // 디카페인펌프
double ctCBScale = 0.0; // 에스프레소 펌프
double ctCoolerScale = 0.0; // 냉동기 
// CT 제한값
double ctCfLimit = 0.0;
double ctCBLimit = 0.0;
double ctCoolerLimit = 0.0;
// CT 제한값
double ctCfInputV= 0.0;
double ctCBInputV = 0.0;
double ctCoolerInputV = 0.0;

// 유량기
int flowLimit1 = 200; // 순환량 제한 => 유량기에서 200ml가 순환했다면
int flowLimit2 = 1000; // 유입량 제한 => 유량기에서 1000ml가 들어왔다면
double totalFlow1 = 0.0; // 순환 유량계에서 나간 양
double totalFlow2 = 0.0; // 유입 유량계에서 나간 양

// Level 초음파 거리측정 센서
int cfLevel = 0;
int coldbrewLevel = 0;
int pvLevelTolerance = 3;
int limitLevel = 100; // 설정값
int limitLevelMin = 200; // 빈 상태 => 값이 높음
int limitLevelMax = 50; // 가득 찬 상태 => 값이 낮음

// 디카페인, 콜드브루 세정횟수
int cfCleanCount = 2; // 필요한 디카페인 세정 횟수
int cfCleanCurrentCount = 0; // 현재 디카페인 세정 횟수
int cfCleanTime = 60;
int cbCleanCount = 2; // 필요한 콜드브루 세정 횟수
int cbCleanCurrentCount = 0; // 현재 콜드브루 세정 횟수
int cbCleanTime = 60;

int timer1 = 1;
int timer2 = 5;
int timer3 = 10;
int timer4 = 60;

Preferences preferences;
boolean coolerStatus = false;
boolean heaterStatus = false;
// 버튼 인터럽 => 냉각 while문 종료용
bool transferInterrupt = false;

