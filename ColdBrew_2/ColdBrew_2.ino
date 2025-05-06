// ColdBrew_2.ino
#include <Arduino.h>
#include <Preferences.h>
#include "wifi_mqtt.h"
#include "variables.h"
#include "switch.h"
#include "pinControl.h"
#include "utils.h"


void setup() {
    Serial.begin(115200);
    // 와이파이 & MQTT 연결
    setWifi();
    setMqtt();
    setupPins();
    delay(1000);
    initMachineValue();
    TimerCheck(1);
    // checkMqttValue();

}

void loop() {
    setWifi();
    setMqtt();
    yield();
    delay(100);
}
