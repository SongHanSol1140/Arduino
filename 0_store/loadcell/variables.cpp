#include "variables.h"

// 와이파이
char wifi_ssid[] = "NNX2-2.4G";
char wifi_password[] = "$@43skshslrtm";
IPAddress wifiIP(192, 168, 0, 251);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
IPAddress dns(192, 168, 0, 1);
// MQTT
char mqttClientName[] = "LoadcellModule";
char mqttUserName[] = "nanonix"; // 아이디
char mqttPassword[] = "$@43nanonix"; // 패스워드
char publishTopic[] = "LoadcellServer";
char subscribeTopic[] = "LoadcellModule";
IPAddress mqttAddress(192, 168, 0, 230);  // MQTT 브로커 IP. 포트는 미기입시 자동 1883



// HX711 객체 정의
HX711 scale(DOUT_PIN, CLK_PIN, 128);

// 핀 정의
const int DOUT_PIN = 16;
const int CLK_PIN = 17;

// 보정값 및 영점값
float calibration_factor = 1068.1;
int calibration_count = 0;
int zeroFactor = 0;
float tolerance = 200;

// 무게 계산을 위한 변수
int currentIndex = 0;;
const int averageSize = 4;
int averageValue[averageSize] = {0};
long sumOfValues = 0;
int average = 0;
float weight = 0.0;
float previous_weight = 0.0;

// 기타 변수
int weightCount = 0;
bool useManual = false;