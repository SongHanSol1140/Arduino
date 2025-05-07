#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>
#include "HX711.h"

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
extern char publishTopic[];
extern char subscribeTopic[];


// HX711 객체를 전역 선언
extern HX711 scale;

// 핀 정의
extern const int DOUT_PIN;  // HX711 데이터 핀
extern const int CLK_PIN;   // HX711 클럭 핀

// 보정값 및 영점값
extern float calibration_factor;  // 보정값
extern int calibration_count;     // 보정값 초기화
extern int zeroFactor;            // 영점값
extern float tolerance;           // 허용 오차

// 이동 평균 계산을 위한 변수
extern int currentIndex;
extern const int averageSize;  // 이동 평균 배열 크기
extern int averageValue[];
extern long sumOfValues;      // 평균 나누기전 값
extern float weight;           // 계산된 무게
extern float previous_weight;  // 영점 조절용 이전 무게 변수


// 기타 변수
extern int weightCount;
extern bool useManual;
#endif  // VARIABLES_H
