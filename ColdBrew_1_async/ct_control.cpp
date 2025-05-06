
#include "ct_control.h"
#include "variables.h"


// double scale1 = 120;
// int limitScale1 = 50;
// int convertedScale1 = 0;
double analogValue1 = 0;
// double scale2 = 120;
// int limitScale2 = 50;
// int convertedScale2 = 0;
double analogValue2 = 0;

void change_scale1(double analogValue) {
    convertedScale1 = analogValue * (scale1 / 4095.0);
}

void change_scale2(double analogValue) {
    convertedScale2 = analogValue * (scale2 / 4095.0);
}

void ctSetup() {
    pinMode(outputSignal1, OUTPUT);
    digitalWrite(outputSignal1, LOW);
    pinMode(outputSignal2, OUTPUT);
    digitalWrite(outputSignal2, LOW);

    pinMode(inputSignal1, INPUT_PULLUP);
    pinMode(inputSignal2, INPUT_PULLUP);
    Serial.println("CT Setup Complete");
}

void updateCTControl() {
    analogValue1 = analogRead(inputSignal1);
    change_scale1(analogValue1);
    if (convertedScale1 > limitScale1) {
        digitalWrite(outputSignal1, HIGH);
    } else {
        digitalWrite(outputSignal1, LOW);
    }

    analogValue2 = analogRead(inputSignal2);
    change_scale2(analogValue2);
    if (convertedScale2 > limitScale2) {
        digitalWrite(outputSignal2, HIGH);
    } else {
        digitalWrite(outputSignal2, LOW);
    }
    // Serial.print("Analog Value 1: ");
    // Serial.println(analogValue1);
    // Serial.print("converted1: ");
    // Serial.println(convertedScale1);
    // Serial.print("Analog Value 2: ");
    // Serial.println(analogValue2);
    // Serial.print("converted2 : ");
    // Serial.println(convertedScale2);
}
