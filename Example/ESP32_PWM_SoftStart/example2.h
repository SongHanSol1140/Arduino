// #include <WiFi.h>

// // PWM 설정
// const int pwmPin = 25;        // PWM 출력 핀
// const int pwmFreq = 50000;    // 50kHz
// const int pwmResolution = 8;  // 8-bit 해상도 (0-255)

// // 버튼 설정
// const int buttonPin = 17;             // 버튼 핀
// volatile bool buttonPressed = false;  // 버튼 눌림 상태
// int lastButtonState = HIGH; 

// // PWM 설정
// const float targetDuty = 60;  // 목표 듀티 사이클 (%)
// const float startDuty = 20;   // 시작 듀티 사이클 (%)
// float currentDuty = 0;        // 현재 듀티 사이클

// // 소프트 스타트 설정
// const int rampTime = 1000;      // 1초 동안 증가
// const int updateInterval = 20;  // 20ms마다 업데이트

// bool pwmRunning = false;  // PWM 실행 상태
// bool softStartComplete = false;  // 소프트 스타트 완료 상태


// void setup() {
//   Serial.begin(115200);

//   // PWM 설정
//   ledcAttach(pwmPin, pwmFreq, pwmResolution);

//   // 버튼 설정
//   pinMode(buttonPin, INPUT_PULLUP);

//   Serial.println("Press the button to start/stop PWM output");
// }

// void loop() {
//   int currentButtonState = digitalRead(buttonPin); // 현재 버튼 상태 읽기
  
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     pwmRunning = !pwmRunning;
//     if(pwmRunning){
//       softStart();
//     }else{
//       stopPWM();
//     }

//   }

//   lastButtonState = currentButtonState; // 현재 상태를 이전 상태로 저장
//   delay(50); // 바운싱 방지를 위한 딜레이
// }

// void softStart() {
//   int steps = rampTime / updateInterval;
//   float dutyStep = (targetDuty - startDuty) / (float)steps;

//   Serial.println("Starting soft start");

//   for (int i = 0; i <= steps; i++) {
//     currentDuty = startDuty + (dutyStep * i);
//     if (currentDuty > targetDuty) currentDuty = targetDuty;

//     int pwmValue = map(currentDuty, 0, 100, 0, 255);
//     ledcWrite(pwmPin, pwmValue);

//     Serial.printf("Current duty: %.2f%%\n", currentDuty);

//     delay(updateInterval);
//   }

//   Serial.println("Soft start completed");
//   Serial.printf("Final duty: %.2f%%\n", currentDuty);
// }

// void stopPWM() {
//   Serial.println("Stopping PWM");
//   ledcWrite(pwmPin, 0);
//   currentDuty = 0;
//   Serial.println("PWM stopped");
//   Serial.printf("Final duty: %.2f%%\n", currentDuty);
// }