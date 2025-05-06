// pinControl.cpp
#include "pinControl.h";
#include "variables.h";

// 핀 초기화
void setupPins() {
    pinMode(hash3, OUTPUT); // #3
    pinMode(hash5, OUTPUT); // #5
    pinMode(hash8, OUTPUT); // #8
    pinMode(hash9, OUTPUT); // #9
    pinMode(hash11, OUTPUT); // #11
    pinMode(hash12, OUTPUT); // #12
    pinMode(hash13, OUTPUT); // #13
    pinMode(hash14, OUTPUT); // #14
    pinMode(hash15, OUTPUT); // #15
    pinMode(hash16, OUTPUT); // #16
    pinMode(hash20, OUTPUT); // #20
    pinMode(hash21, OUTPUT); // #21
    pinMode(hash22, OUTPUT); // #22
    pinMode(hash25, OUTPUT); // #25
    pinMode(hash26, OUTPUT); // #26
    pinMode(hash24, OUTPUT); // #24
    // 모든 핀을 LOW로 설정
    digitalWrite(hash3, LOW);
    digitalWrite(hash5, LOW);
    digitalWrite(hash8, LOW);
    digitalWrite(hash9, LOW);
    digitalWrite(hash11, LOW);
    digitalWrite(hash12, LOW);
    digitalWrite(hash13, LOW);
    digitalWrite(hash14, LOW);
    digitalWrite(hash15, LOW);
    digitalWrite(hash16, LOW);
    digitalWrite(hash20, LOW);
    digitalWrite(hash21, LOW);
    digitalWrite(hash22, LOW);
    digitalWrite(hash25, LOW);
    digitalWrite(hash26, LOW);
    digitalWrite(hash24, LOW);
}

// 핀 제어 함수
void controlPin(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}
