#include "variables.h"
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
// Wi-Fi 정보
char wifi_ssid[] = "NNX2-2.4G";
char wifi_password[] = "$@43skshslrtm";

// MQTT
char mqttClientName[] = "DoorSystem";
char mqttUserName[] = "nanonix"; // 아이디
char mqttPassword[] = "$@43nanonix"; // 패스워드
char publishTopic[] = "LoadCellServer";
char subscribeTopic[] = "LoadCell";

// 기타 변수
int weightCount = 0;
bool useManual = false;