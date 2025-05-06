// pinControl.cpp
#include "pinControl.h";
#include "variables.h";

// 핀 초기화
void setupPins() {
    // 전자변
    pinMode(hash1, OUTPUT);
    pinMode(hash2, OUTPUT);
    pinMode(hash3, OUTPUT);
    pinMode(hash4, OUTPUT);
    pinMode(hash5, OUTPUT);
    pinMode(hash6, OUTPUT);
    pinMode(hash7, OUTPUT);
    pinMode(hash8, OUTPUT);
    pinMode(hash9, OUTPUT);
    pinMode(hash10, OUTPUT);
    pinMode(hash11, OUTPUT);
    pinMode(hash12, OUTPUT);
    pinMode(hash13, OUTPUT);
    pinMode(hash14, OUTPUT);
    pinMode(hash15, OUTPUT);
    pinMode(tmpCoolerPin, OUTPUT);
    
    //쿨러
    digitalWrite(tmpCoolerPin, LOW);
    // 모든 핀을 LOW로 설정
    digitalWrite(hash1, LOW);
    digitalWrite(hash2, LOW);
    digitalWrite(hash3, LOW);
    digitalWrite(hash4, LOW);
    digitalWrite(hash5, LOW);
    digitalWrite(hash6, LOW);
    digitalWrite(hash7, LOW);
    digitalWrite(hash8, LOW);
    digitalWrite(hash9, LOW);
    digitalWrite(hash10, LOW);
    digitalWrite(hash11, LOW);
    digitalWrite(hash12, LOW);
    digitalWrite(hash13, LOW);
    digitalWrite(hash14, LOW);
    digitalWrite(hash15, LOW);
}

// 핀 제어 함수
void controlPin(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}
