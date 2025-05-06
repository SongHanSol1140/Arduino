#include <esp_sleep.h> // ESP32 슬립 기능 사용을 위한 헤더

// RTC 메모리에 저장될 변수 선언 (딥슬립 후에도 값이 유지됨)
// 0: 초기 상태 또는 딥슬립에서 깨어난 직후
// 1: '모뎀 슬립'(라이트 슬립 1단계)에서 깨어난 후
// 2: 라이트 슬립 2단계에서 깨어난 후
RTC_DATA_ATTR int sleep_stage = 0;

// 슬립 시간 설정 (마이크로초 단위)
const uint64_t SLEEP_DURATION_US = 1000 * 1000 * 2; // 2초

void setup() {
  Serial.begin(115200);
  delay(1000); // 시리얼 모니터 연결 시간 확보

  // 어떤 이유로 깨어났는지 확인
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

  // 딥슬립 타이머에 의해 깨어났는지 확인
  if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER && sleep_stage == 0) {
    // 딥슬립 직전에 sleep_stage를 0으로 설정했으므로, 타이머로 깨어나고 stage가 0이면 딥슬립에서 깨어난 것임
    Serial.println("\n-------------------------");
    Serial.println("3 - Woke from Deep Sleep (System Reset)");
    Serial.println("    Restarting the cycle...");
  } else if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER && sleep_stage == 0) {
    // 초기 전원 켜짐
    Serial.println("Initial Power On. Starting sequence...");
  }
  // 라이트 슬립에서 깨어난 경우는 loop() 내에서 처리됨
}

void loop() {
  switch (sleep_stage) {
    case 0: // 단계 1: '모뎀 슬립' (라이트 슬립으로 시연)

    // 모뎀 슬립모드 => 저전력 블루투스 / 와이파이 상태
      Serial.println("\n-------------------------");
      Serial.println("1 - Entering 'Modem Sleep' phase (using Light Sleep for 2s)...");
      Serial.println("    (Concept: If WiFi/BT were active, they could enter low power mode)");

      // 다음 단계를 위해 상태 변수 업데이트
      sleep_stage = 1;

      // 타이머로 2초 후 깨어나도록 설정
      esp_sleep_enable_timer_wakeup(SLEEP_DURATION_US);
      Serial.flush(); // 시리얼 출력 완료 보장

      // 라이트 슬립 시작 (여기서 실행이 잠시 멈춤)
      esp_light_sleep_start();

      // --- 라이트 슬립에서 깨어나면 여기서 실행이 재개되고 loop() 처음으로 돌아감 ---
      break;

    case 1: // 단계 2: 라이트 슬립
      Serial.println("\n-------------------------");
      Serial.println("2 - Woke from 'Modem Sleep' phase.");
      Serial.println("    Entering standard Light Sleep for 2s...");

      // 다음 단계를 위해 상태 변수 업데이트
      sleep_stage = 2;

      // 타이머로 2초 후 깨어나도록 설정
      esp_sleep_enable_timer_wakeup(SLEEP_DURATION_US);
      Serial.flush(); // 시리얼 출력 완료 보장

      // 라이트 슬립 시작 (여기서 실행이 잠시 멈춤)
      esp_light_sleep_start();

      // --- 라이트 슬립에서 깨어나면 여기서 실행이 재개되고 loop() 처음으로 돌아감 ---
      break;

    case 2: // 단계 3: 딥 슬립
      Serial.println("\n-------------------------");
      Serial.println("3 - Woke from standard Light Sleep.");
      Serial.println("    Entering Deep Sleep for 2s...");

      // 딥슬립 후 리셋되면 초기 상태(0)에서 시작하도록 상태 변수 설정
      sleep_stage = 0;

      // 타이머로 2초 후 깨어나도록 설정
      esp_sleep_enable_timer_wakeup(SLEEP_DURATION_US);
      Serial.flush(); // 시리얼 출력 완료 보장

      // 딥 슬립 시작 (여기서 실행이 멈추고, 깨어나면 시스템 리셋됨)
      esp_deep_sleep_start();

      // --- 이 아래 코드는 실행되지 않음 ---
      Serial.println("This will not be printed after deep sleep.");
      break;

    default:
      // 혹시 모를 예외 처리
      Serial.println("Error: Unknown sleep stage! Resetting...");
      sleep_stage = 0;
      delay(1000);
      break;
  }
}