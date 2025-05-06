// int vInputPin = 34;
// const float calibrationFactor = 1.158;
// void setup() {
//   Serial.begin(115200);
//   analogReadResolution(12);
//   delay(1000);
// }

// // 3.3V => 3.3V로 감지 
// void loop() {

//   int adcValue = analogRead(vInputPin);        // 34번 핀에서 ADC 값 읽기
//   float currentVoltage = getVoltage(adcValue); // ADC 값을 전압으로 변환
//   float currentHz = (currentVoltage / 3.3) * 30000; // 전압에 따른 주파수 계산
     
//   Serial.print(currentVoltage, 2); // 평균 전압 출력
//   Serial.print("V / ");-
//   Serial.print(currentHz, 1); // 평균 주파수 출력
//   Serial.println("kz");
//   delay(200); // 0.5(delay(500))초 대기 후 다시 측정
// }

// float getVoltage(int rawAdcValue) {
//   // ESP32의 ADC 최대 값은 4095로 가정
//   float currentVoltage = (rawAdcValue / 4095.0) * 3.3;
//   return currentVoltage;
// }