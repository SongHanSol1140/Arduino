
// max98357.h

#ifndef MAX98357_H
#define MAX98357_H

#include <Arduino.h>
#include <SD.h>
#include "driver/i2s.h"
#include <string.h>

#include "freertos/FreeRTOS.h" // FreeRTOS 헤더
#include "freertos/task.h"    // Task 관련 헤더

struct WAVHeader {
    uint32_t sampleRate;
    uint16_t numChannels;
    uint16_t bitsPerSample;
};
void initI2S(uint32_t sampleRate, uint16_t bitsPerSample, uint16_t numChannels);
void playWav(const char *fileName);
bool readWAVHeader(File &file, WAVHeader &header);
void playWavNonBlocking(const char *fileName);



#endif // MAX98357_H
