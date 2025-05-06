// ColdBrew_2.ino
#include <Arduino.h>
#include <Preferences.h>
#include "wifi_mqtt.h"
#include "variables.h"
#include "switch.h"
#include "pinControl.h"
#include "webPage.h"


void setup() {
    Serial.begin(115200);
    // 와이파이 & MQTT 연결
    WiFi.begin(ssid, password);
    setWifi();
    setMqtt();
    setupPins();
    setupWebPage();
    delay(3000);
    initMachineValue();

}

void loop() {
    setWifi();
    setMqtt();

    delay(100);
}
