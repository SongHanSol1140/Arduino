// #include <Arduino.h>
// #include <PID_v1.h>

// const int ANALOG_PIN = 4;   // 아날로그 입력 핀
// const int SWITCH_PIN = 18;  // 스위치 입력 핀
// const int PWM_PIN = 19;     // PWM 출력 핀

// const int PWM_RESOLUTION = 8;        // PWM 해상도 (8비트: 0-255)
// const int PWM_FREQ = 20000;          // 듀티사이클 100%일 때 주파수 (Hz)
// const float START_DUTY = 10 * 2.55;  // 최소 듀티사이클 10% (25.5)

// double targetPWM, currentPWM, pidOutput;
// double Kp = 2, Ki = 5, Kd = 1;
// PID myPID(&currentPWM, &pidOutput, &targetPWM, Kp, Ki, Kd, DIRECT);

// bool isRunning = false;  // PWM 동작 상태
// bool currentButtonState = false;
// bool lastButtonState = true;

// void setup() {
//   Serial.begin(115200);
//   pinMode(SWITCH_PIN, INPUT_PULLUP);

//   // PWM 설정
//   ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);

//   // PID 제어 설정
//   myPID.SetMode(AUTOMATIC);
//   myPID.SetSampleTime(100);       // 100ms 간격으로 PID 계산
//   myPID.SetOutputLimits(0, 255);  // PID 출력 범위 설정
// }

// void loop() {
//   // 아날로그 입력 읽기 (0~3.3V)
//   int analogValue = analogRead(ANALOG_PIN);
//   // 아날로그 값(0~4095)을 목표 듀티 사이클 값(0~255)으로 변환
//   targetPWM = map(analogValue, 0, 4095, 0, 255);
//   Serial.print("목표 PWM 출력: ");
//   Serial.println(targetPWM);

//   // =====================================================================
//   // PWM 출력 상태 관리
//   currentButtonState = digitalRead(SWITCH_PIN);
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {

//     isRunning = !isRunning;
//     Serial.println("Button Pressed: Toggled");
//     Serial.print("PWM 출력 상태: ");
//     Serial.println(isRunning);

//     // PWM 출력을 시작하거나 중지할 때 PID 제어 모드 설정
//     if (isRunning) {
//       myPID.SetMode(AUTOMATIC);
//     } else {
//       myPID.SetMode(MANUAL);
//       pidOutput = 0;
//     }
//   }
//   lastButtonState = currentButtonState;  // 상태 업데이트

//   // =====================================================================
//   // PID 제어
//   if (isRunning) {
//     currentPWM = analogRead(ANALOG_PIN);  // 현재 PWM 출력 값 읽기
//     myPID.Compute();
    
//     Serial.print("설정값 : ");
//     Serial.println(pidOutput);
//     // 현재 듀티 사이클 적용
//     ledcWrite(ANALOG_PIN, (int)pidOutput);

//     Serial.print("Current PWM Value: ");
//     Serial.println(currentPWM);
//   }

//   // PWM을 끄는 상태 처리
//   if (!isRunning) {
//     ledcWrite(ANALOG_PIN, 0);  // PWM 출력 꺼짐
//   }

//   delay(100);  // 100ms 간격으로 루프 실행
// }