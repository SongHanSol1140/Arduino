// // 유속 측정기
// unsigned long lastDebounceTime = 0;  // 출력 핀이 마지막으로 토글된 시간
// unsigned long debounceDelay = 1000;  // 디바운스 시간; 출력이 깜빡이면 증가합니다.
// int pinInterrupt = 14;

// float Count = 0.0f;
// float totalFlow = 0.0f;  // 누적 유량을 저장할 변수

// void onChange()
// {
//   if (digitalRead(pinInterrupt) == LOW)
//     Count++;
// }

// void setup()
// {
//   Serial.begin(115200); // 시리얼 포트 초기화
//   pinMode(pinInterrupt, INPUT_PULLUP); // 인터럽트 핀 설정

//   // 인터럽트 활성화
//   attachInterrupt(digitalPinToInterrupt(pinInterrupt), onChange, FALLING);
// }

// void loop()
// {
//   if ((millis() - lastDebounceTime) > debounceDelay) {
//     lastDebounceTime = millis();
    
//     float flowRate = Count / 38.0f; // 현재 유량을 ml/s 단위로 계산
//     totalFlow += flowRate;          // 누적 유량에 현재 유량을 더함
    
//     Serial.print("pulse : ");
//     Serial.print(Count);
//     Serial.print("    ");
//     Serial.print(flowRate);
//     Serial.println(" ml/s");

//     Serial.print("Total Flow: ");
//     Serial.print(totalFlow);
//     Serial.println(" ml");

//     Count = 0; // 다음 측정을 위해 Count 초기화
//   }
//   delay(1);
// }
