// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <IPAddress.h>
#include <Arduino.h>
// WIFI

extern char wifi_ssid[];
extern char wifi_password[];
extern IPAddress wifiIP;    // 고정 IP 주소
extern IPAddress gateway;   // 게이트웨이 주소
extern IPAddress subnet;    // 서브넷 마스크
extern IPAddress dns;    // 서브넷 마스크

// Centrex
extern const char *centrexHost;
extern const char *centrex_id;
extern const char *centrex_raw_password;
extern const String *centrex_password;
extern const char *msg;
#endif  // VARIABLES_H
