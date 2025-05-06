// MCP23017.cpp
#include "MCP23017.h"

int hash1 = 0;
int hash2 = 1;
int hash3 = 2;
int hash4 = 3;
int hash5 = 4;
int hash6 = 5;
int hash7 = 6;
int hash8 = 7;
int hash9 = 8;
int hash10 = 9;
int hash11 = 10;
int hash12 = 11;
int hash13 = 12;
int hash14 = 13;  // 콜드브루 펌프
int hash15 = 15;  // 디카페인 펌프
int coolerPin = 32;

// MCP23017
const uint8_t MCP23017_ADDRESS = 0x20;
Adafruit_MCP23X17 mcp23017;

// 핀 초기화
void MCP23017_Setup() {
  // MCP23017
  if (!mcp23017.begin_I2C(MCP23017_ADDRESS)) {
    Serial.println("MCP23017 Expander not found");
    // while(1);
  }
  for (int i = 0; i < 16; i++) {
    mcp23017.pinMode(i, OUTPUT);
  }

  // 모두 Low로 설정
  mcp23017.writeGPIOA(0x00); // HIGH
  mcp23017.writeGPIOB(0xFF); // LOW
  
  Serial.println("MCP23017_Setup Complete");
}

// 핀 제어 함수
void controlPin(int pin, bool state) {
  digitalWrite(pin, state ? HIGH : LOW);
}
