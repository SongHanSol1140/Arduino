// webPage.h
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <WiFi.h>
// 웹서버
// #include <WebServer.h>
// extern WebServer server;

// 비동기 웹서버
#include <ESPAsyncWebServer.h>
extern AsyncWebServer server;

void setupWebPage();
#endif // WEBPAGE_H
