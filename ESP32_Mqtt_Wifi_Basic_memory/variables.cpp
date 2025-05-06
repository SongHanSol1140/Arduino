#include "variables.h"

// 와이파이 정보
char wifi_ssid[] = "NNX2-2.4G"; // 접속할 와이파이명
char wifi_password[] = "$@43skshslrtm"; //접속할 와이파이 비밀번호
IPAddress wifiIP(192, 168, 0, 230);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크

// MQTT 정보
char mqttClientName[] = "ESP32_MqttTestSubscriber"; // 주의 : 하나의 mqtt에서 기기별 mqtt Name은 유일해야함,
char mqttUserName[] = "nanonix"; // mqtt 접속 아이디/패스워드 사용시 사용할 값, (현재는 사용하지않음)
char mqttPassword[] = "$@43nanonix"; // mqtt 접속 아이디/패스워드 사용시 사용할 값, (현재는 사용하지않음)

char topic[] = "test/topic";
IPAddress mqttAddress(192, 168, 0, 19);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883
