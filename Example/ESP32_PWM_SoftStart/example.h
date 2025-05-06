// #include <Arduino.h>

// const int ANALOG_PIN = 12;  // 아날로그 입력 핀
// const int SWITCH_PIN = 18;   // 스위치 입력 핀
// const int PWM_PIN = 19;      // PWM 출력 핀

// const int PWM_RESOLUTION = 8;        // PWM 해상도 (8비트: 0-255)
// const int PWM_FREQ_MAX = 15;         // 듀티사이클 100% 주파수
// const float PWM_FREQ_MIN = 10 * 2.55;  // 최소 듀티사이클 10% (25.5)

// int targetFreq = PWM_FREQ_MIN;  // 목표 듀티사이클
// float currentFreq = PWM_FREQ_MIN; // 현재 듀티사이클

// bool isRunning = false;  // PWM 동작 상태
// bool currentButtonState = false;
// bool lastButtonState = true;

// const int totalSteps = 30;     // 3초 동안 30단계로 변화
// int stepCounter = 0;           // 루프 카운터

// void setup() {
//   Serial.begin(115200);
//   pinMode(SWITCH_PIN, INPUT_PULLUP);

//   // PWM 설정
//   ledcAttach(PWM_PIN, PWM_FREQ_MAX, PWM_RESOLUTION);
// }

// void loop() {
//   // 아날로그 입력 읽기 (0~3.3V)
//   int analogValue = analogRead(ANALOG_PIN);
//   // 아날로그 값(0~4095)을 목표 듀티 사이클 값(25.5~255)으로 변환
//   targetFreq = map(analogValue, 0, 4095, 0, 255);

//   Serial.print("Analog Value: ");
//   Serial.print(analogValue);
//   Serial.print(", Voltage: ");
//   Serial.print((analogValue / 4095.0) * 3.3);
//   Serial.print("V, Target Duty Cycle: ");
//   Serial.println(targetFreq);

//   // =====================================================================
//   // PWM 출력 상태 관리
//   currentButtonState = digitalRead(SWITCH_PIN);
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     isRunning = !isRunning;
//     Serial.println("Button Pressed: Toggled");
//     Serial.print("PWM출력상태: ");
//     Serial.println(isRunning);

//     if (isRunning) {
//       // 소프트 스타트 시작 시 최소 듀티사이클에서 시작
//       currentFreq = PWM_FREQ_MIN;
//       stepCounter = 0;  // 소프트 스타트 시작 시 루프 카운터 초기화
//     } else {
//       // 종료 시 듀티 사이클 초기화
//       currentFreq = PWM_FREQ_MIN;
//       stepCounter = 0;  // 종료 시에도 루프 카운터 초기화
//     }
//   }
//   lastButtonState = currentButtonState;  // 상태 업데이트

//   // =====================================================================
//   // 소프트 스타트 동작
//   if (isRunning && stepCounter < totalSteps) {
//     // 목표 듀티사이클까지 변화해야 하는 단계 수 계산
//     float stepSize = (targetFreq - PWM_FREQ_MIN) / totalSteps;  // 목표까지 30단계로 변화

//     // 목표 듀티사이클로 서서히 변화시키기 (증가 또는 감소)
//     currentFreq += stepSize;  // 서서히 변화

//     // 현재 듀티 사이클 적용
//     ledcWrite(PWM_PIN, (int)currentFreq);
    
//     Serial.print("Current Duty Cycle: ");
//     Serial.println(currentFreq);

//     stepCounter++;  // 루프 카운터 증가
//   }

//   // PWM을 끄는 상태 처리
//   if (!isRunning) {
//     ledcWrite(PWM_PIN, 0);  // PWM 출력 꺼짐
//   }

//   delay(100);  // 100ms 간격으로 루프 실행
// }
