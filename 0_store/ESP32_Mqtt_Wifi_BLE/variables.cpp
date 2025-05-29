// variables.cpp
#include "variables.h"

// 지점코드
char branchCode[] = "Nanonix";

// 와이파이
char wifi_ssid[] = "NNX2-2.4G";
// char wifi_ssid[] = "nnx-factory2.4";
char wifi_password[] = "$@43skshslrtm";
// char wifi_password[] = "nanonix817";
IPAddress wifiIP(192, 168, 0, 231);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
IPAddress dns(192, 168, 0, 1);

// MQTT
char mqttClientName[] = "CleaningbotModule";
char mqttUserName[] = "nanonix";           // 아이디
char mqttPassword[] = "$@43nanonix";       // 패스워드
char serverTopic[] = "Server";;
char moduleTopic[] = "Module";;

IPAddress mqttAddress(192, 168, 0, 230);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883
