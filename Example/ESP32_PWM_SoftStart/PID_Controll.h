// #include <Arduino.h>
// #include <PID_v1.h>

// const int ANALOG_PIN = 25;                // 아날로그 VCC 입력 핀
//   const int SWITCH_PIN = 18;              // 스위치 입력 핀(풀업, GND / GPIO에 연결)
// const int PWM_PIN = 19;                   // PWM 출력 핀
// double targetPWM, currentPWM, pwmOutput;  // PID제어 변수

// // 목표 Hz
// double targetHz = 5000;

// // PID설정
// double Kp = 0.5, Ki = 0.02, Kd = 0.01;













// // =====================================================================
// // 주파수 설정
// const int PWM_FREQ = 1500;     // 주파수 //
// const int PWM_RESOLUTION = 8;  // PWM 해상도 (8비트: 0-255, 10비트: 0-1023, 12비트: 0-4095)
// PID myPID(&currentPWM, &pwmOutput, &targetPWM, Kp, Ki, Kd, DIRECT);




// bool isRunning = true;  // PWM 동작 상태
// bool currentButtonState = false;
// bool lastButtonState = true;

// void setup() {
//   Serial.begin(115200);
//   // 스위치 버튼
//   pinMode(SWITCH_PIN, INPUT_PULLUP);



//   // PWM 설정
//   ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);
//   // PID 제어 설정
//   Serial.println("PWM Control Start");
//   Serial.println("Mode AUTOMATIC");
//   myPID.SetMode(AUTOMATIC);
//   // Serial.println("Mode MANUAL");
//   // myPID.SetMode(MANUAL);
//   myPID.SetOutputLimits(25, 255);
//   delay(1000);
// }

// void loop() {
//   // PWM 출력 상태 관리
//   currentButtonState = digitalRead(SWITCH_PIN);
//   // 버튼 상태 변화 감지
//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     isRunning = !isRunning;
//     Serial.println("Button Pressed: Toggled");
//     Serial.print("PWM 출력 상태: ");
//     Serial.println(isRunning);
//     if (isRunning) {
//       Serial.println("AUTOMATIC");
//       myPID.SetMode(AUTOMATIC);
//     } else {
//       Serial.println("MANUAL");
//       myPID.SetMode(MANUAL);
//     }
//   }
//   lastButtonState = currentButtonState;  // 상태 업데이트

//   // =====================================================================
//   Serial.println("===================");
//   Serial.print("CurrentPWM : ");
//   Serial.println(currentPWM);
//   Serial.print("targetPWM : ");
//   Serial.println(targetPWM);
//   Serial.print("pwmOutput : ");
//   Serial.println(pwmOutput);
//   // 아날로그 입력 읽기 (0~3.3V)
//   int analogValue = analogRead(ANALOG_PIN);


//   if (isRunning) {
//     currentPWM = (double)analogValue / 4095.0 * 255.0;
//     // 아날로그 값(0~4095)을 목표 듀티 사이클 값(0~255)으로 변환
//     targetPWM = targetHz / 15000 * 255;

//     myPID.Compute();
//     // ledcWrite(PWM_PIN, (int)pwmOutput);
//     ledcWrite(PWM_PIN, (int)pwmOutput);

//     // 테스트 종료시 주석처리
//     Serial.println("ON");
//     Serial.print("입력 : ");
//     // Serial.println(currentPWM);
//     Serial.println((double)analogValue / 4095.0 * 15000);
//     Serial.print("목표 PWM: ");
//     // Serial.print(targetPWM);
//     Serial.print(targetPWM / 255 * 15000);
//     Serial.println("Hz");
//     Serial.print("설정 PWM: ");
//     // Serial.print(pwmOutput);
//     Serial.print(pwmOutput / 255 * 15000);
//     Serial.println("Hz");


//   } else {
//     currentPWM = 0;
//     targetPWM = 0;
//     pwmOutput = 0;
//     myPID.Compute();
//     ledcWrite(PWM_PIN, 0);
//     Serial.println("OFF");
//     Serial.print("입력 : ");
//     Serial.println((double)analogValue / 4095.0 * 15000);
//     Serial.print("목표 PWM: ");
//     Serial.print(targetPWM / 255 * 15000);
//     Serial.println("Hz");
//     Serial.print("설정 PWM: ");
//     Serial.print(pwmOutput / 255 * 15000);
//     Serial.println("Hz");
//   }


//   delay(100);
// }

// /**
//   1. Kp (Proportional Gain, 비례 게인)
//     정의: 비례 게인(Kp)은 현재 오차에 비례하여 출력값을 결정하는 요소입니다.
//     작동 원리: 오차(목표값과 현재값의 차이)가 클수록 더 큰 출력이 생성됩니다. Kp는 이 오차에 얼마나 강하게 반응할지를 결정합니다. 예를 들어, Kp 값이 클수록 시스템이 더 빠르게 반응하지만, 오버슈트(목표값을 초과하는 현상)가 발생할 가능성이 높습니다.
//     효과:
//     Kp가 너무 낮을 경우: 반응이 너무 느려서 목표값에 도달하는 데 오랜 시간이 걸립니다.
//     Kp가 너무 클 경우: 시스템이 과도하게 반응하여 목표값을 넘어서거나, 진동하면서 불안정해질 수 있습니다.
//   2. Ki (Integral Gain, 적분 게인)
//     정의: 적분 게인(Ki)은 오차의 누적에 비례하여 출력값을 조정하는 요소입니다.
//     작동 원리: 시간이 지남에 따라 오차가 누적되면, Ki가 그 누적된 오차를 보정하려고 출력값을 증가시킵니다. 이는 **잔여 오차(steady-state error)**를 제거하는 데 유용합니다. Ki는 장기적인 오차를 줄이기 위해 동작합니다.
//     효과:
//     Ki가 너무 낮을 경우: 시스템이 목표값에 도달하지 못하고, 목표값 근처에서 일정한 오차가 계속 남을 수 있습니다.
//     Ki가 너무 클 경우: 적분 누적이 너무 빠르게 이루어져서 시스템이 과도하게 반응하거나 진동하게 될 수 있습니다.
//   3. Kd (Derivative Gain, 미분 게인)
//     정의: 미분 게인(Kd)은 오차의 변화율(즉, 오차가 얼마나 빠르게 변하는지)에 비례하여 출력값을 조정하는 요소입니다.
//     작동 원리: Kd는 오차의 변화가 급격할 때 이를 억제하려는 역할을 합니다. 이는 과도 현상이나 진동을 줄이는 데 도움을 줍니다. Kd는 시스템의 반응 속도를 안정화시키는 데 중요한 역할을 합니다.
//     효과:
//     Kd가 너무 낮을 경우: 과도 현상이나 진동이 발생할 수 있습니다.
//     Kd가 너무 클 경우: 시스템이 지나치게 천천히 반응할 수 있습니다.
//     PID 게인의 조합 효과
//     Kp: 빠른 반응을 제공합니다. 너무 크면 불안정해질 수 있습니다.
//     Ki: 장기적인 오차를 보정합니다. 너무 크면 진동을 유발할 수 있습니다.
//     Kd: 과도 현상과 진동을 억제합니다. 너무 크면 시스템이 느려질 수 있습니다.
// */
