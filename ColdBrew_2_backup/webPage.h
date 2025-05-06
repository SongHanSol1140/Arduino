// webPage.h
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <WiFi.h>
// 웹서버
#include <WebServer.h>
extern WebServer server;

// 비동기 웹서버
// #include <ESPAsyncWebServer.h>
// extern AsyncWebServer server;

void setupWebPage();
void handleRoot();
void handleNotFound();
void handleCoffeeCleaning();
void handleCoffeeLowerCleaning();
void handleDecafCycleCleaning();
void handleDecafTankTransfer();
void handleDecafBottleTransfer();
void handleColdeBrewTransfer();

void handleColdBrewExtraction();
void handleColdBrewCooling();
void handleColdBrewTransfer();
void handleDecafExtraction();
void handleDecafCooling();
void handleDecafTransfer();




void handleStatus();
void handleTmpSet1();
void handleTmpSet2();
void handleFlowLimit1();
void handleFlowLimit2();
void handleDecafClean();
void handleColdBrewClean();
#endif // WEBPAGE_H
