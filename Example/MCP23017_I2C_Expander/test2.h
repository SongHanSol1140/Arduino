/*  PA0~3 HIGH / PA4~7 LOW
    PB0~3 LOW / PA4~7 HIGH
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


// mcp23017.ino
#include <Wire.h>
#include "mcp23017.h"
void printBinary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        Serial.print((value >> i) & 1);
    }
}
void setup() {
    Serial.begin(115200);
    Wire.begin();

    // MCP23017 초기화 및 설정
    Mcp23017_Init();
    
    // PORTA를 출력으로 설정
    Set_port_dir(PORTA, MOUTPUT);
    
    // PORTB를 출력으로 설정
    Set_port_dir(PORTB, MOUTPUT);
    
    // PA0~3를 HIGH로, PA4~7를 LOW로 설정
    Write_gpio(PORTA, 0b00001111); // 0b00001111(0x0F)
    
    // PB0~3를 LOW로, PB4~7를 HIGH로 설정
    Write_gpio(PORTB, 0b11110000); // 0b11110000(0xF0)

    // 설정 값 확인 출력
    Serial.print("PORTA: 0x");
    Serial.println(Read_gpio(PORTA), HEX);
    Serial.print("PORTB: 0x");
    Serial.println(Read_gpio(PORTB), HEX);
}

void loop() {
    delay(5000); // 5초 대기

    // PA7만 HIGH로 설정 (다른 핀 상태는 유지)
    uint8_t portA_val = Read_gpio(PORTA); // 현재 PORTA 값 읽기
    Serial.print("읽은값 : ");
    printBinary(Read_gpio(PORTA));
    Serial.print("변경할값 : ");
    portA_val |= 0b10000000; // PA7 비트만 HIGH로 설정 => |= 가 중요함
    printBinary(portA_val);
    Write_gpio(PORTA, portA_val); // 새로운 PORTA 값 쓰기
    Serial.print("변경된 값 : ");
    printBinary(Read_gpio(PORTA));

    // 설정 값 확인 출력
    Serial.println("Setting PA7 to HIGH");
    Serial.print("PORTA: 0x");
    Serial.println(Read_gpio(PORTA), HEX);

    // 이후 루프를 반복하지 않도록 무한 대기
    while (1) {
        delay(1000);
    }
}


*/