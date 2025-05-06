// // https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html
// #include <Arduino.h>
// //
// const float MIN_PERCENT = 10.0;     // 최소 듀티사이클(0~100%)
// const float TARGET_PERCENT = 50.0;  // 목표 듀티사이클(0~100%)
// const int HZ_LIMIT = 1000;           // Hz제한

// /* 
//   1. 입력 압력(25번핀에 입력)이 HZ_LIMIT을 넘으면 26번 핀에서 출력 HIGH
//      다시내려간다면 LOW
//   2. 18번핀 스위치 누를시 19번핀에서 목표 듀티사이클 값으로 2초에걸쳐 PWM출력올라감
//      다시 누를시 PWM출력 0
// */


// // ==============================
// const int ANALOG_PIN = 25;       // 아날로그 입력 핀
// const int LIMIT_CHECK_PIN = 26;  // 출력값보다 낮으면 LOW / 높으면 HIGH
// const int SWITCH_PIN = 18;       // 스위치 입력 핀
// const int PWM_PIN = 19;          // PWM 출력 핀
// float inputHz = 0;               // 입력된압력 관리용 변수












// const int PWM_RESOLUTION = 8;                 // PWM 해상도 (8비트: 0-255)
// const float START_DUTY = MIN_PERCENT * 2.55;  // 최소 듀티사이클 10% * 25.5
// float targetPWM = TARGET_PERCENT * 2.55;      // 목표 듀티사이클




// const int PWM_FREQ = 1500;  //주파수 설정

// float currentPWM = START_DUTY;  // 현재 듀티사이클

// bool isRunning = false;  // PWM 동작 상태
// bool currentButtonState = false;
// bool lastButtonState = true;

// const int totalSteps = 20;  // 이동 평균 배열 크기
// int pwmArray[totalSteps];   // 이동 평균 계산을 위한 PWM 값 배열
// int pwmIndex = 0;           // 배열 인덱스

// void setup() {
//   Serial.begin(115200);
//   // 스위치 핀
//   pinMode(SWITCH_PIN, INPUT_PULLUP);

//   // 출력 핀
//   pinMode(LIMIT_CHECK_PIN, OUTPUT);
//   digitalWrite(LIMIT_CHECK_PIN, LOW);
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
//   inputHz = analogValue / 4095.0 * 15000.0;
//   // 아날로그 값(0~4095)을 목표 듀티 사이클 값(25.5~255)으로 변환

//   Serial.print("Input Hz : ");
//   Serial.print(inputHz);
//   Serial.print(" / PWM 0-255 : ");
//   Serial.println((analogValue / 4095.0) * 255);
//   Serial.print("현재출력 PWM: ");
//   if (isRunning) {
//     Serial.println(currentPWM);
//   } else {
//     Serial.println(0);
//   }

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
//   // 출력에 따라 LIMIT_CHECK_PIN LOW / HIGH
//   if (isRunning == HIGH) {
//     if (inputHz < HZ_LIMIT) {
//       Serial.println("압력 기준치 미만");
//       digitalWrite(LIMIT_CHECK_PIN, LOW);
//     } else {
//       Serial.println("압력 기준치 초과");
//       digitalWrite(LIMIT_CHECK_PIN, HIGH);
//     }
//   } else {
//     Serial.println("압력 미체크");
//     digitalWrite(LIMIT_CHECK_PIN, LOW);
//   }
//   // ========== ===========================================================
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
//   }

//   // PWM 끄기
//   if (!isRunning) {
//     ledcWrite(PWM_PIN, 0);  // PWM 출력 꺼짐
//   }


//   delay(100);
// }