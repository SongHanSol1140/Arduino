const int dacPin1 = 25; // 1.65V를 출력할 핀
const int dacPin2 = 26; // 3.3V를 출력할 핀
const int inputPin1 = 16; // 디지털 입력을 받을 핀 (풀업)
const int inputPin2 = 17; // 디지털 입력을 받을 핀 (풀업)


const float targetV = 1.65;
void setup() {
  Serial.begin(115200);

  // DAC 설정
  dacWrite(dacPin1, 116);
  dacWrite(dacPin2, 77); 
  
  Serial.println("DAC 설정 완료");

  // 입력 핀을 풀업으로 설정
  pinMode(inputPin1, INPUT_PULLUP);
  pinMode(inputPin2, INPUT_PULLUP);

  Serial.println("입력 핀 설정 완료");
}

void loop() {
  // 16번 핀 상태 읽기
  int inputState1 = digitalRead(inputPin1);
  Serial.print("16번 핀 상태: ");
  if (inputState1 == HIGH) {
    Serial.println("HIGH");
  } else {
    Serial.println("LOW");
  }

  // 17번 핀 상태 읽기
  int inputState2 = digitalRead(inputPin2);
  Serial.print("17번 핀 상태: ");
  if (inputState2 == HIGH) {
    Serial.println("HIGH");
  } else {
    Serial.println("LOW");
  }
  Serial.print("25번핀 출력상태 : ");
  Serial.print(targetV);
  Serial.println("V");
  // 1초 대기
  delay(1000);
}
