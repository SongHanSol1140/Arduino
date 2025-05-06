
// PIM517.cpp
#include "PIM517.h"
#include <PIM517_Library.h>

const uint8_t PIM517_ADDRESS = 0x18;
IOExpander pim517(Wire, PIM517_ADDRESS);

// 입력핀
const int pim517_tmpHeaterInputPin = 7;
const int pim517_tmpColdbrewInputPin = 9; 
const int pim517_tmpCoffeeInputPin = 11;

void PIM517_Setup() {
  //PIM517 초기화
  if (!pim517.initialise()) {
    Serial.println("PIM517 Expander not found");
  }
  pim517.setAdcVref(3.3f);  // PIM517 IO Expander의 입력 전압
  pim517.setMode(pim517_tmpHeaterInputPin, IOExpander::PIN_ADC);
  pim517.setMode(pim517_tmpColdbrewInputPin, IOExpander::PIN_ADC);
  pim517.setMode(pim517_tmpCoffeeInputPin, IOExpander::PIN_ADC);

  if (!pim517.initialise()) {
    Serial.println("PIM517 Expander not found");
  }
  delay(1000);

  // PID 모드 설정
  heaterPID.SetMode(AUTOMATIC);
}


// 콜드브루 PID 출력핀
const int heaterOutputPin = 26;

double adcMax = 4095.0;
double Vs = 3.3;

float R1 = 10000.0;   // voltage divider resistor value // 저항
float Beta = 3950.0;  // Beta value // Beta 값
float To = 298.15;    // Temperature in Kelvin for 25 degree Celsius 
float Ro = 50000.0;   // Resistance of Thermistor at 25 degree Celsius // 25도에서의 저항값

// PID 출력을 위한설정
// 콜드브루만 출력
double tmpCbSetPoint = 30.0;
double tmpCbInput = 0;
double tmpCbOutput = 0;
float tmpCfLimit = 100.0;
float tmpCbLimit = 100.0;
float tmpHeaterLimit = 100.0;

double Kp=2, Ki=5, Kd=1;                 // 온도계 PID 계수
PID heaterPID(&tmpCbInput, &tmpCbOutput, &tmpCbSetPoint, Kp, Ki, Kd, DIRECT);

void tmpColdbrewCalcurate(){
  double Vout, Rt = 0;
  double T, Tc, Tf = 0;

  double voltInput = 0;
  double average = 0;

  for(int i = 0; i < 5; i++){
    voltInput = pim517.inputAsVoltage(pim517_tmpColdbrewInputPin);
    average += voltInput;
  }
  voltInput = average/5;
  Serial.print("입력전압 : ");
  Serial.print(voltInput);
  Serial.println("V");

  Rt = R1 * voltInput / (Vs - voltInput);
  
  Serial.print("Rt : ");
  Serial.println(Rt);
  T = 1/(1/To + log(Rt/Ro)/Beta);    // Temperature in Kelvin
  Tc = T - 273.15;                   // Celsius
  Tf = Tc * 9 / 5 + 32;              // Fahrenheit
  
  tmpCbInput = Tc;

  Serial.print("콜드브루 현재 온도 : ");
  Serial.println(Tc);

  heaterPID.Compute();
  //Limit on
  double limit = (255.0/100.0) * tmpCbLimit;
  if(tmpCbOutput > limit){
    tmpCbOutput = int(limit);
  }
  Serial.print("콜드브루 현재 PID출력 : ");
  Serial.println(tmpCbOutput);
}








// 