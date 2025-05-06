// MCP23017.h
#ifndef MCP23017_H
#define MCP23017_H

#include <Adafruit_MCP23X17.h>

// 핀 설정
// 전자변
extern int hash1;
extern int hash2;
extern int hash3;
extern int hash4;
extern int hash5; 
extern int hash6;
extern int hash7;
extern int hash8;
extern int hash9;
extern int hash10;
extern int hash11;
extern int hash12;
extern int hash13;
extern int hash14;
extern int hash15;
// 온도 냉동기 ON/OFF PIN
extern int coolerPin;


void MCP23017_Setup();
void controlPin(int pin, bool state);

#endif  // MCP23017_H
