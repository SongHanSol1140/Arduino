// variables.cpp
#include "variables.h"

//사용 핀
// CT #1, #2
int outputSignal1 = 32;
int outputSignal2 = 33;
int inputSignal1 = 34;
int inputSignal2 = 35;
// 
int coldbrewLevelPin = 27;
// MQTT 토픽
char mqttClientName[] = "coldbrew_ESP32_1";
char coldBrewSetup[] = "coldbrewMachineSetup";
char coldBrewMachine[] = "coldbrewMachine";

// PT100ohm
// 입력온도
double tmpInput1 = 0;
double tmpInput2 = 0;
// 출력
double tmpOutput1 = 0;
double tmpOutput2 = 0;
// 목표온도
double setTmpPoint1 = 35.0;
double setTmpPoint2 = 35.0;
double tmpOutLimit1 = 100.0;
double tmpOutLimit2 = 100.0;


int tmpTolerance = 2; // 온도 허용치, 목표온도보다 이만큼 내려가면 냉동기를 다시킴


// 펌프 작동여부
bool coolingStatus = false;

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
double FlowRate1 = 0; // 2번 유량기 속도
double FlowRate2 = 0; // 1번 유량기 속도
int flowLimit1 = 500; // 송출량 제한 => 1번 유량기에서 500ml가 나갔다면
int flowLimit2 = 1000; // 송출량 제한 => 2번 유량기에서 1000ml가 나갔다면
double totalFlow1 = 0; // 1번 유량기에서 나간 액체의 양
double totalFlow2 = 0; // 2번 유량기에서 나간 액체의 양

// Level 초음파 거리측정 센서
int decafLevel = 0;
int coldbrewLevel = 0;
int limitLevel = 100; // 설정값
int limitLevelMin = 200; // 빈 상태 => 값이 높음
int limitLevelMax = 20; // 가득 찬 상태 => 값이 낮음

// 디카페인, 콜드브루 세정횟수
int decafCleanCount = 1;
int decafCleanTime = 60;
int cbCleanCount = 1;
int cbCleanTime = 60;

int timer1 = 60000; // 60초 (1분)
int timer2 = 300000; // 300초 (5분)
int timer3 = 600000; //600초 (10분)
int timer4 = 3600000; // 3600초(1시간)

Preferences preferences;
