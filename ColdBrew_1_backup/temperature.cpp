//temperature.cpp
#include "temperature.h"
#include "variables.h"
// 온도센서 및 PID 제어 변수 선언
// Adafruit_MAX31865(int8_t spi_cs, int8_t spi_mosi, int8_t spi_miso, int8_t spi_clk);
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(5, 19, 18, 23);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(15, 13, 12, 14);

#define RREF 430.0 // 저항
#define RNOMINAL 100.0
#define PID_OUT1 21
#define PID_OUT2 22
#define PID_OUT1_ALARM 25
#define PID_OUT2_ALRAM 26

double Kp = 2, Ki = 5, Kd = 1;
PID myPID1(&tmpInput1, &tmpOutput1, &setTmpPoint1, Kp, Ki, Kd, DIRECT);
PID myPID2(&tmpInput2, &tmpOutput2, &setTmpPoint2, Kp, Ki, Kd, DIRECT);

void initTemperatureControl() {
    thermo1.begin(MAX31865_3WIRE);
    myPID1.SetMode(AUTOMATIC);
    pinMode(PID_OUT1_ALARM, OUTPUT);
    thermo2.begin(MAX31865_3WIRE);
    myPID2.SetMode(AUTOMATIC);
    pinMode(PID_OUT2_ALRAM, OUTPUT);
    Serial.println("온도센서1, 2 세팅완료");
}

void updateTemperatureControl() {
    // PT100ohm 센서 읽기 및 PID 제어
    // 제한이 100이상일시 100으로 제한


    // 디카페인
    if(tmpOutLimit1 > 100){tmpOutLimit1 = 100;};
    tmpInput1 = thermo1.temperature(RNOMINAL, RREF);
    myPID1.Compute();
    if (tmpOutput1 > (255.0 / 100.0) * tmpOutLimit1) {
        tmpOutput1 = (255.0 / 100.0) * tmpOutLimit1;
    }
    analogWrite(PID_OUT1, tmpOutput1);

    // 냉각기 - 목표온도보다 높으면 냉각기를 켜고, 목표온도보다 tmpTolerance만큼 낮으면 냉각기를 끈다
    if(coolingStatus){
      if (tmpInput1 > setTmpPoint1) {
          digitalWrite(PID_OUT1_ALARM, HIGH);
      } else if (tmpInput1 < setTmpPoint1 - tmpTolerance) {
          digitalWrite(PID_OUT1_ALARM, LOW);
          
      }
    }else{
      digitalWrite(PID_OUT1_ALARM, LOW);
    }




    // 콜드브루
    if(tmpOutLimit2 > 100){tmpOutLimit2 = 100;};
    // 2번은 PWM출력을 내보내지 않음
    tmpInput2 = thermo2.temperature(RNOMINAL, RREF);
    myPID2.Compute();
    if (tmpOutput2 > (255.0 / 100.0) * tmpOutLimit2) {
        tmpOutput2 = (255.0 / 100.0) * tmpOutLimit2;
    }
    analogWrite(PID_OUT2, tmpOutput2);

    // 냉각기 - 목표온도보다 높으면 냉각기를 켜고, 목표온도보다 tmpTolerance만큼 낮으면 냉각기를 끈다
    if(coolingStatus){
      if (tmpInput2 > setTmpPoint2) {
          digitalWrite(PID_OUT2_ALRAM, HIGH);
      } else if (tmpInput2 < setTmpPoint2 - tmpTolerance) {
          digitalWrite(PID_OUT2_ALRAM, LOW);
      }
    }else{
      digitalWrite(PID_OUT2_ALRAM, LOW);
    }


    // 출력확인
    // Serial.print("Sensor 1 PID Output (before limiting): ");
    // Serial.println(tmpOutput1);
    // Serial.print("Sensor 2 PID Output (before limiting): ");
    // Serial.println(tmpOutput2);
}
