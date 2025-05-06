// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H
#include <IPAddress.h>
// 지점코드
extern char branchCode[];

// WIFI
extern char wifi_ssid[];
extern char wifi_password[];
extern IPAddress wifiIP;    // 고정 IP 주소
extern IPAddress gateway;   // 게이트웨이 주소
extern IPAddress subnet;    // 서브넷 마스크
extern IPAddress dns;    // 서브넷 마스크
// MQTT
extern char mqttClientName[];  // MQTT접속할 클라이언트 이름
extern char mqttUserName[];    // mqtt유저명
extern char mqttPassword[];    // mqtt패스워드명
extern char serverTopic[];
extern char moduleTopic[];
extern IPAddress mqttAddress; // MQTT 브로커의 IP 주소

// TCP PORT
extern int TCP_PORT;
// 출입문
extern int openTime;                        // 출입문 개방시간
extern int waitForOpenTime;                 // 출입문 개방 대기시간(센서감지)
extern int closingTime;                     // 출입문이 닫히는 시간
extern unsigned long doorOpenTime;          // 출입문이 열린 시간을 저장
extern bool doorIsOpen;                     // 출입문이 열려 있는지 상태를 저장
extern unsigned long doorClosingStartTime;  // 출입문이 닫히기 시작한 시간을 저장
extern bool doorIsClosing;                  // 출입문이 닫히는 중인지 상태를 저장
extern bool doorWaitingForOpen;             // 출입문 개방 대기 상태
extern unsigned long doorWaitStartTime;     // 개방 대기 시작 시간
extern bool audioPlay;

// PIN SETUP
extern int ENTRY_SENSOR_PIN;
extern int EXIT_SENSOR_PIN;
extern int Emergency_BUTTON_PIN;
extern int DOOR_PIN;

// SD Card Module Pin 
extern int SD_SCK_PIN;
extern int SD_MISO_PIN;
extern int SD_MOSI_PIN;
extern int SD_CS_PIN;

// MAX95387 AMP Pin I2S 설정
extern int I2S_LRCLK_PIN;
extern int I2S_BCLK_PIN;
extern int I2S_DATA_PIN;
extern int READ_BUF_LEN;

#endif  // VARIABLES_H
