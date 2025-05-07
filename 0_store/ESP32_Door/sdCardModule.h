#ifndef SDCARDMODULE_H
#define SDCARDMODULE_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

bool initSDCard();
bool checkFileExists(const char* filename);

#endif // SDCARDMODULE_H
