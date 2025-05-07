// variables.cpp
#include "variables.h"

// 지점코드
char branchCode[] = "Nanonix";

// 와이파이
char wifi_ssid[] = "NNX2-2.4G";
char wifi_password[] = "$@43skshslrtm";
IPAddress wifiIP(192, 168, 0, 231);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
IPAddress dns(192, 168, 0, 1);

// MQTT
char mqttClientName[] = "CleaningbotModule";
char mqttUserName[] = "nanonix";           // 아이디
char mqttPassword[] = "$@43nanonix";       // 패스워드
char serverTopic[] = "CleaningbotServer";;
char moduleTopic[] = "CleaningbotModule";;
IPAddress mqttAddress(192, 168, 0, 230);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883

// Pin
const uint16_t checkInPlace = 9;
const uint16_t checkInTable = 10;
const uint16_t IR_TX = 4;

// 각종 state
char cleaningbotRuningState = false;
int sec1 = 0;
int sec2 = 0;
int sec3 = 0;
int timerSet1 = 0;
int timerSet2 = 0;
int timerSet3 = 0;