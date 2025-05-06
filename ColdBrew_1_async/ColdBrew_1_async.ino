// ColdeBrew_1.ino
#include <Arduino.h>
#include <Preferences.h>
#include "wifi_mqtt.h"
#include "web_server.h"
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
    setWebPage();
    setMqtt();
    initTemperatureControl();
    ctSetup();
    flowSensorSetup();
    levelSensorSetup();
    delay(1000);


    // Preferences 시작
    preferences.begin("ColdBrew", false); // 네임스페이스 이름, false는 읽기-쓰기 모드

    // Preferences에서 값 불러오기
    // 두번째 인자는 기본값
    tmpInput1 = 0; // 입력값 => 현재온도
    tmpInput2 = 0; // 입력값 => 현재온도
    tmpOutput1 = preferences.getDouble("tmpOutput1", 0); // 
    tmpOutput2 = preferences.getDouble("tmpOutput2", 0);
    setTmpPoint1 = preferences.getDouble("setTmpPoint1", 35.0);
    setTmpPoint2 = preferences.getDouble("setTmpPoint2", 35.0);
    tmpOutLimit1 = preferences.getDouble("tmpOutLimit1", 100.0);
    tmpOutLimit2 = preferences.getDouble("tmpOutLimit2", 100.0);

    scale1 = preferences.getInt("scale1", 120);
    scale2 = preferences.getInt("scale2", 120);
    limitScale1 = preferences.getInt("limitScale1", 35);
    limitScale2 = preferences.getInt("limitScale2", 60);
    convertedScale1 = 0;
    convertedScale2 = 0;
    FlowRate1 = 0;
    FlowRate2 = 0;
    flowLimit1 = preferences.getInt("flowLimit1", 500);
    flowLimit2 = preferences.getInt("flowLimit2", 1000);
    totalFlow1 = 0.0;
    totalFlow2 = 0.0;
    decafLevel = 0;
    coldbrewLevel = 0;
    limitLevel = preferences.getInt("limitLevel", 100);
    limitLevelMin = preferences.getInt("limitLevelMin", 200);
    limitLevelMax = preferences.getInt("limitLevelMax", 20);

    decafCleanCount = preferences.getInt("decafCleanCount", 1);  
    decafCleanTime = preferences.getInt("decafCleanTime", 60);
    cbCleanCount = preferences.getInt("cbCleanCount", 1);
    cbCleanTime = preferences.getInt("cbCleanTime", 60);

    timer1 = preferences.getInt("timer1", 300);
    timer2 = preferences.getInt("timer2", 5);
    timer3 = preferences.getInt("timer3", 10);
    timer4 = preferences.getInt("timer4", 60);


}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        setWifi();
    }
    if (!client.connected()) {
        setMqtt();
    }
    client.loop();
   // 비동기 방싱그
    // server.handleClient();
    updateTemperatureControl();
    updateCTControl();
    updateFlowSensor();
    updateDecafSensor();
    updateColdBrewSensor();
    client.loop();
    updatePv();
    delay(50);
}
