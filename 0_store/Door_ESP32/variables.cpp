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
char mqttClientName[] = "DoorSystem_ESP32";
char mqttUserName[] = "nanonix";           // 아이디
char mqttPassword[] = "$@43nanonix";       // 패스워드
char serverTopic[] = "DoorServer";;
char moduleTopic[] = "DoorModule";;
IPAddress mqttAddress(192, 168, 0, 230);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883

// TCP PORT
int TCP_PORT = 8001;

// 출입문 변수
int openTime = 5;                        // 문개방 시간(MQTT 통신불가시 기본값)
int waitForOpenTime = 10;                // 출입문 개방 대기시간(MQTT 통신불가시 기본값)
int closingTime = 2000;                  // 문 닫힘 시간(2000 => 2초)
unsigned long doorOpenTime = 0;          // 문이 열린 시간을 저장
bool doorIsOpen = false;                 // 문이 열려 있는지 상태를 저장
unsigned long doorClosingStartTime = 0;  // 문이 닫히기 시작한 시간을 저장
bool doorIsClosing = false;              // 문이 닫히는 중인지 상태를 저장
bool doorWaitingForOpen = false;         // 출입문 개방 대기 상태
unsigned long doorWaitStartTime = 0;     // 개방 대기 시작 시간
bool audioPlay = false;

// PIN SETUP
int ENTRY_SENSOR_PIN = 16;
int EXIT_SENSOR_PIN = 17;
int Emergency_BUTTON_PIN = 18;
int DOOR_PIN = 19;

// SD Card Module Pin
int SD_SCK_PIN = 21;
int SD_MISO_PIN = 22;
int SD_MOSI_PIN = 23;
int SD_CS_PIN = 5;

// MAX95387 AMP Pin I2S 설정
int I2S_LRCLK_PIN = 27;
int I2S_BCLK_PIN = 26;
int I2S_DATA_PIN = 25;
int READ_BUF_LEN = 1024;