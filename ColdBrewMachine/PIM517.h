// PIM517.h
#ifndef PIM517_H
#define PIM517_H

#include <Arduino.h>
#include <PID_v1.h>

// 히터 설정값
extern double tmpCbSetPoint;
extern double tmpCbInput;
extern double tmpCbOutput;
// 온도제한
extern float tmpCfLimit;
extern float tmpCbLimit;
extern float tmpHeaterLimit;
// PID 객체를 외부에서 참조할 수 있도록 선언
extern PID heaterCoffeePID;
extern PID heaterColdbrewPID;

extern int tmpTolerance;

// 함수
void PIM517_Setup();
void tmpSetup();
void tmpCoffeeCalcurate();
void tmpColdbrewCalcurate();
void tmpHeaterCalcurate();

#endif // PIM517_H
