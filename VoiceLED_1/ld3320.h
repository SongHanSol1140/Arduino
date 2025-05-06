#ifndef LD3320_H
#define LD3320_H

#include <Arduino.h>
#include <SPI.h> // SPI 라이브러리 포함

#define MIC 0x0b
#define MONO 0x23
#define CLK_IN         24
#define PLL_11         (uint8_t)((CLK_IN/2.0)-1)
#define PLL_ASR_19     (uint8_t)(CLK_IN*32.0/(PLL_11+1) - 0.51)
#define PLL_ASR_1B     0x48
#define PLL_ASR_1D     0x1f
extern int WR;
class VoiceRecognition {
public:
    VoiceRecognition();

    void update();
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
    void writeReg(uint8_t address, uint8_t value);
    uint8_t readReg(uint8_t address);
    void cSHigh(void);
    void cSLow(void);
    static void IRAM_ATTR updateWrapper();
    int check_b2();
};

#endif // LD3320_H
