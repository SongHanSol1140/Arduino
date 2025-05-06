// irSetup.h
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t IR_TX = 4;
// ESP01M GPPIO 0이나 2에 연결
IRsend irsend(IR_TX);

void sendPowerIR();
void sendHomeIR();
void sendPauseWorkIR();
void setIR();



// 전원On/Off
const uint16_t PowerIR[44] = {
  3000, 2450, 550, 450,  550, 1400, 550, 450,
  550,  1450, 550, 400,  550, 1450, 550, 1450,
  500,  450,  550, 450,  550, 450,  550, 450,
  550,  450,  500, 450,  550, 450,  550, 1450,
  500,  1450, 550, 1450, 550, 1400,  550, 1450,
  550,  1400, 550
};

// 충전(HomeIR)
const uint16_t HomeIR[44] = {
  3050, 2400, 550, 450,  550, 1400, 600, 450,
  500,  1450, 550, 450,  550, 1400, 550, 450,
  550,  1450, 550, 450,  550, 400,  550, 450,
  550,  450,  550, 400,  600, 1400, 550, 450,
  550,  1450, 550, 1400, 550, 1450, 550, 1400,
  550,  1450, 550
};

// 청소 시작/정지
const uint16_t PauseWorkIR[44] = {
  3050, 2450, 550, 400,  550, 1450, 550, 450,
  550,  1400, 550, 450,  550, 1450, 550, 1400,
  550,  450,  550, 1450, 550, 450,  500, 1450,
  550,  450,  550, 450,  550, 400,  550, 1450,
  550,  450,  550, 1400, 550, 450,  550, 1450,
  550,  1400, 550
};

void sendPowerIR(){
    Serial.println("전원 ON/OFF");
    irsend.sendRaw(PowerIR, 44, 38);  // Send a raw data capture at 38kHz.
}
void sendHomeIR(){
    Serial.println("홈 IR신호 발생");
    irsend.sendRaw(HomeIR, 44, 38);  // Send a raw data capture at 38kHz.
}
void sendPauseWorkIR(){
    Serial.println("시작/정지 IR신호 발생");
    irsend.sendRaw(PauseWorkIR, 44, 38);  // Send a raw data capture at 38kHz.
}