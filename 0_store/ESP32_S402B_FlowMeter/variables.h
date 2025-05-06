
// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H
extern char mqttClientName[]; // MQTT접속할 클라이언트 이름
extern char mqttUserName[]; // mqtt유저명
extern char mqttPassword[]; // mqtt패스워드명
extern char topic[];

extern char wifi_ssid[];
extern char wifi_password[];

extern volatile int pulseCount;
extern float flowRate;
extern float flowMilliLitres;
extern float totalMilliLitres;
extern float nowTime;          
extern unsigned long checkTime;

extern bool isFlowing;
extern unsigned long lastPulseTime;
extern bool wasFlowStopped;

const int FLOW_SENSOR_PIN = 14; // 상수로 선언
#endif // VARIABLES_H
