// variables.cpp
#include "variables.h"

// 와이파이
char wifi_ssid[] = "NNX2-2.4G";
char wifi_password[] = "$@43skshslrtm";
IPAddress wifiIP(192, 168, 0, 254);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
IPAddress dns(192, 168, 0, 1);
// MQTT
char mqttClientName[] = "DoorSystemTelephone";
char mqttUserName[] = "nanonix"; // 아이디
char mqttPassword[] = "$@43nanonix"; // 패스워드
char topic[] = "DoorTelephone";
IPAddress mqttAddress(192, 168, 0, 230);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883

// 핀번호
int TELEPHONE_PIN = 16; // 수화기 빨간선에 연결
// 16번 핀 - 빨간색
// HIGH - 전화 받지 않음 - 수화기 내림
// LOW - 전화 받음 - 수화기 올림
// 아무런 핀설정을 하지않은 핀 17번에 파란선 연결
// 라즈베리파이에서 TCP서버로 발신인 번호를 받는순간 해당 ESP32로 callcancel 요청을 보냄