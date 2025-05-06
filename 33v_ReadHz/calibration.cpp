// int vInputPin = 34;
// const float maxADCVoltage = 3.3;
// const int adcResolution = 4095;
// const int tableSize = 16;  // 보정 테이블의 크기

// // 보정 테이블 (측정된 전압 => 실제 입력 전압)
// // measuredVals: ADC에서 변환된 전압 값
// // actualVals: 실제 입력 전압 값
// float measuredVals[tableSize] = {0.0, 0.08, 0.24, 0.41, 0.52, 0.86, 1.05, 1.15, 1.22, 1.33, 1.49, 1.76, 1.77, 2.26, 2.87, 3.30};
// float actualVals[tableSize]   = {0.0, 0.16, 0.33, 0.50, 0.66, 1.00, 1.20, 1.32, 1.40, 1.50, 1.65, 1.98, 2.00, 2.50, 3.00, 3.30};

// void setup() {
//   Serial.begin(115200);
//   analogReadResolution(12);
//   delay(1000);
// }

// void loop() {
//   int adcValue = analogRead(vInputPin);    // 34번 핀에서 ADC 값 읽기
//   float rawVoltage = getVoltage(adcValue);   // ADC 값을 전압으로 변환 (측정 전압)
//   float calibratedVoltage = calibrateVoltage(rawVoltage); // 보정된(실제) 전압 계산
  
//   // 보정된 전압을 기준으로 주파수 계산 (최대 3.3V일 때 15000khz)
//   float currentHz = (calibratedVoltage / maxADCVoltage) * 30000;
     
//   Serial.print(calibratedVoltage, 2); // 보정된 전압 출력 (소수점 둘째 자리)
//   Serial.print("V / ");
//   Serial.print(currentHz, 1);         // 주파수 출력 (소수점 첫째 자리)
//   Serial.println("khz");
  
//   delay(200); // 0.5초 대기 후 재측정
// }

// // ADC 원시 값을 전압으로 변환하는 함수
// float getVoltage(int rawAdcValue) {
//   float voltage = (rawAdcValue / float(adcResolution)) * maxADCVoltage;
//   return voltage;
// }

// // 측정된 전압을 보정하여 실제 입력 전압으로 변환하는 함수 (선형 보간법 사용)
// float calibrateVoltage(float measured) {
//   // 측정 전압이 보정 테이블의 첫 번째 점보다 작으면 첫 두 점을 이용해 선형 외삽
//   if (measured <= measuredVals[0]) {
//     float slope = (actualVals[1] - actualVals[0]) / (measuredVals[1] - measuredVals[0]);
//     return actualVals[0] + slope * (measured - measuredVals[0]);
//   }
  
//   // 측정 전압이 보정 테이블의 마지막 점보다 크면 마지막 두 점을 이용해 선형 외삽
//   if (measured >= measuredVals[tableSize - 1]) {
//     float slope = (actualVals[tableSize - 1] - actualVals[tableSize - 2]) / (measuredVals[tableSize - 1] - measuredVals[tableSize - 2]);
//     return actualVals[tableSize - 1] + slope * (measured - measuredVals[tableSize - 1]);
//   }
  
//   // 보정 테이블 내에서 선형 보간법으로 실제 전압 계산
//   for (int i = 0; i < tableSize - 1; i++) {
//     if (measured >= measuredVals[i] && measured <= measuredVals[i+1]) {
//       float fraction = (measured - measuredVals[i]) / (measuredVals[i+1] - measuredVals[i]);
//       return actualVals[i] + fraction * (actualVals[i+1] - actualVals[i]);
//     }
//   }
  
//   // 예외 상황(여기까지 도달하면 없어야 함)
//   return measured;
// }