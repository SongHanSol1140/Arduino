/*  input 읽기
    PA0~1 => HIGH
    PA3~4 => LOW
    PA6~7 => INPUT

    PB0~1 => HIGH
    PB3~4 => LOW
    PB6~7 => INPUT
    각 4,5번은 아무것도 설정하지않음(미사용)
basic_mcp23017.cpp / .h

example : https://github.com/seengreat/MCP23017-SG-IO-E017/blob/main/Arduino/mcp23017/mcp23017.ino
 * Project  :
 * Experimental Platform :Arduino UNO + MCP23017 IO Expansion Module
 * Hardware Connection :Arduino UNO -> MCP23017 IO Expansion Module in wiringpi number
 *    5V --> VCC
 *    GND  --> GND
 *    SDA --> SDA 
 *    SCL --> SCL
 *    D2   --> INTA
 *    D3   --> INTB
 * Author  : Andy Li
 * Web Site  : www.seengreat.com

#include <Wire.h>
#include "mcp23017.h"

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // MCP23017 초기화 및 설정
    Mcp23017_Init();
    
    // PORTA를 출력으로 설정 (PA0~1 HIGH, PA3~4 LOW)
    Set_port_dir(PORTA, 0b11001100); // PA6~7 INPUT
    Write_gpio(PORTA, 0b00000011);   // PA0~1 HIGH, PA3~4 LOW

    // PORTB를 출력으로 설정 (PB0~1 HIGH, PB3~4 LOW)
    Set_port_dir(PORTB, 0b11001100); // PB6~7 INPUT
    Write_gpio(PORTB, 0b00000011);   // PB0~1 HIGH, PB3~4 LOW

    // PORTA, PORTB 상태 확인 출력
    Serial.print("PORTA: 0b");
    printBinary(Read_gpio(PORTA));
    Serial.println();
    Serial.print("PORTB: 0b");
    printBinary(Read_gpio(PORTB));
    Serial.println();
}

void loop() {
    // PA6~7과 PB6~7의 입력 상태 읽기
    uint8_t portA_val = Read_gpio(PORTA);
    uint8_t portB_val = Read_gpio(PORTB);

    Serial.print("PA6: ");
    Serial.print((portA_val & 0b01000000) ? "HIGH" : "LOW");
    Serial.print(", PA7: ");
    Serial.print((portA_val & 0b10000000) ? "HIGH" : "LOW");

    Serial.print(", PB6: ");
    Serial.print((portB_val & 0b01000000) ? "HIGH" : "LOW");
    Serial.print(", PB7: ");
    Serial.println((portB_val & 0b10000000) ? "HIGH" : "LOW");

    delay(1000); // 1초 대기
}

// 8비트 이진수로 값을 출력하는 함수
void printBinary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        Serial.print((value >> i) & 1);
    }
}

 /*
