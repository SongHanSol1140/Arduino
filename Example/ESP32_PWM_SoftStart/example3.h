// // https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html
// #include <Arduino.h>

// const int ANALOG_PIN = 4;  // 아날로그 입력 핀
// const int SWITCH_PIN = 18;  // 스위치 입력 핀
// const int PWM_PIN = 19;     // PWM 출력 핀

// const int PWM_RESOLUTION = 8;        // PWM 해상도 (8비트: 0-255)
// const int PWM_FREQ = 20000;             // 듀티사이클 100%일 때 주파수 (Hz)
// const float START_DUTY = 10 * 2.55;  // 최소 듀티사이클 10% (25.5)

// int targetPWM = START_DUTY;     // 목표 듀티사이클
// float currentPWM = START_DUTY;  // 현재 듀티사이클

// bool isRunning = false;  // PWM 동작 상태
// bool currentButtonState = false;
// bool lastButtonState = true;

// const int totalSteps = 30;  // 이동 평균 배열 크기
// int pwmArray[totalSteps];   // 이동 평균 계산을 위한 PWM 값 배열
// int pwmIndex = 0;           // 배열 인덱스

// void setup() {
//   Serial.begin(115200);
//   pinMode(SWITCH_PIN, INPUT_PULLUP);

//   // PWM 설정
//   ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);

//   // 이동 평균 배열 초기화
//   for (int i = 0; i < totalSteps; i++) {
//     pwmArray[i] = START_DUTY;
//   }
// }

// void loop() {
//   // 아날로그 입력 읽기 (0~3.3V)
//   int analogValue = analogRead(ANALOG_PIN);
//   // 아날로그 값(0~4095)을 목표 듀티 사이클 값(25.5~255)으로 변환
//   targetPWM = map(analogValue, 0, 4095, 0, 255);

//   // Serial.print("Analog Value: ");
//   // Serial.print(analogValue);
//   // Serial.print(", Voltage: ");
//   // Serial.print((analogValue / 4095.0) * 3.3);
//   // Serial.print("V, Target Duty Cycle: ");
//   // Serial.print(targetPWM);
//   // Serial.print(", Current PWM: ");
//   // Serial.println(currentPWM);

//   // =====================================================================
//   // PWM 출력 상태 관리
//   currentButtonState = digitalRead(SWITCH_PIN);
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     isRunning = !isRunning;
//     Serial.println("Button Pressed: Toggled");
//     Serial.print("PWM출력상태: ");
//     Serial.println(isRunning);

//     // PWM 출력을 시작할 때 이동 평균 배열과 변수 초기화
//     if (isRunning) {
//       for (int i = 0; i < totalSteps; i++) {
//         pwmArray[i] = START_DUTY;
//       }
//       pwmIndex = 0;
//       currentPWM = START_DUTY;
//     }
//   }
//   lastButtonState = currentButtonState;  // 상태 업데이트

//   // =====================================================================
//   // 이동 평균 계산
//   if (isRunning) {
//     // 이동 평균 배열 업데이트
//     pwmArray[pwmIndex] = targetPWM;
//     pwmIndex = (pwmIndex + 1) % totalSteps;

//     // 이동 평균 계산
//     float sum = 0;
//     for (int i = 0; i < totalSteps; i++) {
//       sum += pwmArray[i];
//     }
//     currentPWM = sum / totalSteps;

//     // 현재 듀티 사이클 적용
//     ledcWrite(PWM_PIN, (int)currentPWM);

//     Serial.print(" / Current Duty Cycle: ");
//     Serial.println(currentPWM);
//   }

//   // PWM을 끄는 상태 처리
//   if (!isRunning) {
//     ledcWrite(PWM_PIN, 0);  // PWM 출력 꺼짐
//   }

//   delay(100);  // 100ms 간격으로 루프 실행
// }