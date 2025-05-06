// webPage.h
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;

void setupWebServer();
extern const char index_html[];

#endif