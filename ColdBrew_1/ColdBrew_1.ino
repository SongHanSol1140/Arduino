// ColdeBrew_1.ino
#include <Arduino.h>
#include <Preferences.h>
#include "wifi_mqtt.h"
#include "temperature.h"
#include "ct_control.h"
#include "flow_sensor.h"
#include "level_sensor.h"
// 설정객체
#include "variables.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Adafruit MAX31865 + PT100ohm, CT, LevelSensor, FlowSensor Test!");
    // 데이터 얻기

    // 와이파이 & MQTT 연결
    setWifi();
    setMqtt();
    temperatureSetup();
    ctSetup();
    flowSensorSetup();
    levelSensorSetup();
    delay(1000);


    // Preferences 시작
    preferences.begin("coldbrew", false); // 네임스페이스 이름, false는 읽기-쓰기 모드
    
    // 두번째 인자는 기본값
    // 온도
    
    tmpSetCfP = preferences.getDouble("tmpSetCfP", 0.0);
    tmpSetCBP = preferences.getDouble("tmpSetCBP", 0.0);
    tmpCfOutput = preferences.getDouble("tmpCfOutput", 0.0);
    tmpCBOutput = preferences.getDouble("tmpCBOutput", 0.0);
    tmpCf_CO = preferences.getDouble("tmpCf_CO", 10.0);
    tmpCB_EX = preferences.getDouble("tmpCB_EX", 25.0);
    tmpCB_CO = preferences.getDouble("tmpCB_CO", 10.0);
    tmpBr_EX = preferences.getDouble("tmpBr_EX", 25.0);
    tmpBr_CO = preferences.getDouble("tmpBr_CO", 10.0);
    tmpCfOLimit = preferences.getDouble("tmpCfOLimit", 100.0);
    tmpCBOLimit = preferences.getDouble("tmpCBOLimit", 100.0);
    // CT
    ctCfScale = preferences.getDouble("ctCfScale", 1.1);
    ctCBScale = preferences.getDouble("ctCBScale", 1.1);
    ctCoolerScale = preferences.getDouble("ctCoolerScale", 0.1);
    ctCfLimit = preferences.getDouble("ctCfLimit", 0.1);
    ctCBLimit = preferences.getDouble("ctCBLimit", 0.1);
    ctCoolerLimit = preferences.getDouble("ctCoolerLimit", 0.1);

    // 유량계
    FlowRate1 = 0;
    FlowRate2 = 0;
    flowLimit1 = preferences.getInt("flowLimit1", 500);
    flowLimit2 = preferences.getInt("flowLimit2", 1000);
    totalFlow1 = 0.0;
    totalFlow2 = 0.0;
    cfLevel = 0;
    coldbrewLevel = 0;
    limitLevel = preferences.getInt("limitLevel", 100);
    limitLevelMin = preferences.getInt("limitLevelMin", 200);
    limitLevelMax = preferences.getInt("limitLevelMax", 20);

    cfCleanCount = preferences.getInt("cfCleanCount", 1);  
    cfCleanTime = preferences.getInt("cfCleanTime", 60);
    cbCleanCount = preferences.getInt("cbCleanCount", 1);
    cbCleanTime = preferences.getInt("cbCleanTime", 60);

    timer1 = preferences.getInt("timer1", 300);
    timer2 = preferences.getInt("timer2", 5);
    timer3 = preferences.getInt("timer3", 10);
    timer4 = preferences.getInt("timer4", 60);


}

void loop() {
    setWifi();
    setMqtt();

    updateTemperatureControl();
    yield();

    updateCTControl();
    yield();

    updateFlowSensor();
    yield();

    updateCfSensor();
    yield();

    updateColdBrewSensor();
    yield();
    
    sendStatus();
    delay(100);
}
