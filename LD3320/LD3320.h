// LD3320.h

#ifndef LD3320_H
#define LD3320_H

#include <Arduino.h>
#include <Wire.h>
#include "SPI.h"

#define uint8 unsigned char
//#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define MIC 0x0b
#define MONO 0x23
#define uint8 unsigned char
#define CLK_IN            24 /// 주파수
#define PLL_11            (uint8)((CLK_IN/2.0)-1)
#define PLL_ASR_19        (uint8)(CLK_IN*32.0/(PLL_11+1) - 0.51)
#define PLL_ASR_1B        0x48
#define PLL_ASR_1D        0x1f

/** SPI 마스터 출력 슬레이브 입력 핀 */
#define SPI_MOSI_PIN   23
/** SPI 마스터 입력 슬레이브 출력 핀 */
#define SPI_MISO_PIN   19
/** SPI 클럭 핀 */
#define SPI_SCK_PIN   18
#define IRQ_PIN 4

#define  RSTB  5 // RSTB 핀 정의
#define  CS  15 // CS 핀 정의

class VoiceRecognition
{
public:
    VoiceRecognition();

    void reset();
    void init(uint8_t mic=MIC);
    void ASR_init();
    unsigned char start();
    void addCommand(char *pass, int num);
    int read();

    void micVol(uint8_t vol);
    void speechEndpoint(uint8_t speech_endpoint_);
    void speechStartTime(uint8_t speech_start_time_);
    void speechEndTime(uint8_t speech_end_time_);
    void voiceMaxLength(uint8_t voice_max_length_);
    void noiseTime(uint8_t noise_time_);

private:

};

void writeReg(unsigned char address, unsigned char value); // 레지스터에 쓰기
unsigned char readReg(unsigned char address); // 레지스터에서 읽기
byte transfer(byte _data); // 데이터 전송
void cSHigh(void);  // CS 핀을 HIGH로 설정
void cSLow(void);  // CS 핀을 LOW로 설정
void update(); // 업데이트 함수
int check_b2(); // 0xB2 레지스터 상태 확인 함수

#endif
