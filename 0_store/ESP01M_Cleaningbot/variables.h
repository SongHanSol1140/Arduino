// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <IPAddress.h>

// 와이파이 정보
extern char wifi_ssid[];
extern char wifi_password[];
extern IPAddress wifiIP;    // 고정 IP 주소
extern IPAddress gateway;   // 게이트웨이 주소
extern IPAddress subnet;    // 서브넷 마스크
extern IPAddress dns;    // 서브넷 마스크


// MQTT 정보
extern char mqttClientName[]; // MQTT 접속 클라이언트 이름
extern char mqttUserName[];   // mqtt 유저명
extern char mqttPassword[];   // mqtt 패스워드명
extern char topic[];
extern IPAddress mqttAddress; // MQTT 브로커의 IP 주소
extern char serverTopic[];
extern char moduleTopic[];

// Pin번호
extern const uint16_t checkInPlace;
extern const uint16_t checkInTable;

// 각종 state
extern char cleaningbotRuningState;

extern int sec1;
extern int sec2;
extern int sec3;
extern int timerSet1;
extern int timerSet2;
extern int timerSet3;

#endif // VARIABLES_H