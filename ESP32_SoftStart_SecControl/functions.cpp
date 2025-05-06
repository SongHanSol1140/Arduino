// functions.cpp
#include "functions.h"

void setupESP32() {
  // 핀 모드 설정
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(PWM_PIN, OUTPUT);

  // PWM 설정
  ledcAttach(PWM_PIN, PWM_FREQUENCY, PWM_RESOLUTION);

  // 단계 수 및 듀티 사이클 증가량 계산
  steps = (int)(softStartDuration / incrementDelay);
  dutyCycleIncrement = (targetDutyCycle - minDutyCycle) / steps;
}

void switchControl() {
  // 스위치 상태 읽기
  currentButtonState = digitalRead(SWITCH_PIN);

  // 버튼 눌림 감지 (풀업이므로 LOW가 눌림)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    isRunning = !isRunning;  // 상태 토글
    if (isRunning) {
      Serial.println("Switch ON");
    } else {
      Serial.println("Switch OFF");
    }
  }
  lastButtonState = currentButtonState;
}

void softStartPWM() {
  static float currentDutyCycle = 0.0;
  static int currentStep = 0;

  if (isRunning) {
    if (currentStep < steps) {
      currentDutyCycle = minDutyCycle + dutyCycleIncrement * currentStep;
      currentStep++;
    } else {
      currentDutyCycle = targetDutyCycle;
    }

    // 듀티 사이클을 PWM 값으로 변환
    int pwmValue = (int)(currentDutyCycle / 100.0 * ((1 << PWM_RESOLUTION) - 1));

    // PWM 출력
    ledcWrite(PWM_PIN, pwmValue);

    // 증가 간격 대기
    delay((int)incrementDelay);
  } else {
    // PWM 출력 중지
    ledcWrite(PWM_PIN, 0);
    currentDutyCycle = minDutyCycle;
    currentStep = 0;
  }
}
