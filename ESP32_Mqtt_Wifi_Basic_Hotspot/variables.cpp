#include "variables.h"

/*
  휴대폰의 핫스팟을 2.4Ghz, 혹은 호환성 최대화로 설정해주세요.
*/


// 와이파이 정보
char wifi_ssid[] = "HanSol"; // 접속할 핫스팟명
char wifi_password[] = "English1!"; //접속할 핫스팟 비밀번호
IPAddress wifiIP(172, 20, 10, 12);  // 접속할 고정 IP 주소
IPAddress gateway(172, 20, 10, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 240);    // 서브넷 마스크
// MQTT 정보
char mqttClientName[] = "ESP32_MqttTestSubscriber"; // 주의 : 하나의 mqtt에서 기기별 mqtt Name은 유일해야함,
char mqttUserName[] = "nanonix"; // mqtt 접속 아이디/패스워드 사용시 사용할 값,
char mqttPassword[] = "$@43nanonix"; // mqtt 접속 아이디/패스워드 사용시 사용할 값,
char topic[] = "test";
IPAddress mqttAddress(172, 20, 10, 11);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883
