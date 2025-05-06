// const int CT_CONTROL_PIN = 34;  // 모터 전류 측정핀
// const int NUM_READS = 10;       // 평균을 낼 읽기 횟수

// // 평균을 계산하는 함수
// int readAnalogAverage(int pin, int numReads) {
//   long sum = 0;  // long 타입 사용하여 합계가 넘치지 않도록 설정

//   // 지정된 횟수만큼 analogRead를 수행하고 그 합을 구함
//   for (int i = 0; i < numReads; i++) {
//     sum += analogRead(pin);
//     delay(10);
//   }

//   // 평균 계산
//   return sum / numReads;
// }
// void setup() {
//   Serial.begin(115200);
 
// }

// void loop() { 
//   int analogValue = readAnalogAverage(CT_CONTROL_PIN, NUM_READS);

//   Serial.println(analogValue);
//   Serial.print("Vcc : ");
//   Serial.print(analogValue / 4095.0 * 3.3, 3);
//   Serial.println("V");
//   delay(100);
// }