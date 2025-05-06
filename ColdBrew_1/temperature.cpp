// temperature.cpp
#include "temperature.h"
#include "variables.h"

// 써미스터 설정
#define SERIESRESISTOR 5000 

const float adcMax = 4095.0; // ADC resolution 12-bit (0-4095)
const float Vs = 3.3;        // supply voltage 
const float R1 = 10000.0;   // voltage divider resistor value
const float Beta = 3976.0;  // Beta value
const float To = 298.15;    // Temperature in Kelvin for 25 degree Celsius
const float Ro = 50000.0;   // Resistance of Thermistor at 25 degree Celsius

double Kp = 2, Ki = 5, Kd = 1;
PID myPID1(&tmpCfInput, &tmpCfOutput, &tmpSetCfP, Kp, Ki, Kd, DIRECT);
PID myPID2(&tmpCBInput, &tmpCBOutput, &tmpSetCBP, Kp, Ki, Kd, DIRECT);

const int numReadings = 5;
float cfReadings[numReadings];
float cbReadings[numReadings];
int readIndex = 0;
float cfTotal = 0;
float cbTotal = 0;

float calculateTemperature(int thermistorPin) {
    float adc = analogRead(thermistorPin);  
    float Vout = adc * Vs / adcMax;
    float Rt = R1 * Vout / (Vs - Vout);  
    float T = 1 / (1 / To + log(Rt / Ro) / Beta);  // Temperature in Kelvin
    return T - 273.15;  // Return temperature in Celsius
}

void temperatureSetup() {
    // 온도계 PID
    myPID1.SetMode(AUTOMATIC);
    myPID2.SetMode(AUTOMATIC);

    // PWM 주파수와 해상도 설정 / 8비트 0~255 12비트 0~4095
    const int freq = 5000;
    const int resolution = 8;

    // 콜드브루 온도감지 PWM출력
    ledcAttach(tmpCBPIDPin, freq, resolution);

    // 이동평균 초기화
    for (int i = 0; i < numReadings; i++) {
        cfReadings[i] = 0;
        cbReadings[i] = 0;
    }
}

void updateTemperatureControl() {
    // 1. 디카페인 온도 측정
    float cfTemp = calculateTemperature(tmpCfInputPin);
    cfTotal = cfTotal - cfReadings[readIndex];
    cfReadings[readIndex] = cfTemp;
    cfTotal = cfTotal + cfReadings[readIndex];
    tmpCfInput = cfTotal / numReadings;
    // Serial.print("디카페인 온도 : ");
    // Serial.println(tmpCfInput);

    // 2. 콜드브루 온도 측정
    float cbTemp = calculateTemperature(tmpCBInputPin);
    cbTotal = cbTotal - cbReadings[readIndex];
    cbReadings[readIndex] = cbTemp;
    cbTotal = cbTotal + cbReadings[readIndex];
    tmpCBInput = cbTotal / numReadings;

    readIndex = (readIndex + 1) % numReadings;

    // 제한
    if(tmpCBOLimit > 100) {
        tmpCBOLimit = 100;
    }

    // Cf는 PWM 출력을 내보내지 않음
    double maxOutput = (255.0 / 100.0) * tmpCBOLimit;
    if (tmpCBOutput > maxOutput) {
        tmpCBOutput = maxOutput;
    }
    myPID2.Compute();
    // PWM 출력
    ledcWrite(tmpCBPIDPin, tmpCBOutput);
    // Serial.print("콜드브루 온도 : ");
    // Serial.println(tmpCBInput);
    // Serial.print(": / 콜드브루 출력 : ");
    // Serial.println("tmpCBOutput");
}