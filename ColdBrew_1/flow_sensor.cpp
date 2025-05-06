#include <Arduino.h>
#include "flow_sensor.h"
#include "variables.h"

volatile int NbTopsFan1 = 0;
volatile int NbTopsFan2 = 0;
unsigned long lastTime1 = 0;
unsigned long lastTime2 = 0;
unsigned long interval = 1000;

void IRAM_ATTR rpm1() {
    NbTopsFan1++;
}

void IRAM_ATTR rpm2() {
    NbTopsFan2++;
}

void flowSensorSetup() {
    pinMode(flowMeterPin1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(flowMeterPin1), rpm1, RISING);
 // #23 
    pinMode(flowMeterPin2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(flowMeterPin2), rpm2, RISING);


    Serial.println("Flow Sensor Setup Complete");

}

void updateFlowSensor() {
    unsigned long currentTime = millis();



    if (currentTime - lastTime1 >= interval) {
        lastTime1 = currentTime;

        noInterrupts();
        float flowLMin1 = (NbTopsFan1 * 1.0) / 38.0;
        NbTopsFan1 = 0;
        interrupts();

        FlowRate1 = (flowLMin1 * 1000.0) / 60.0;
        totalFlow1 += FlowRate1;
    }

    if (currentTime - lastTime2 >= interval) {
        lastTime2 = currentTime;

        noInterrupts();
        float flowLMin2 = (NbTopsFan2 * 1.0) / 38.0;
        NbTopsFan2 = 0;
        interrupts();

        FlowRate2 = (flowLMin2 * 1000.0) / 60.0;
        totalFlow2 += FlowRate2;
    }
}
