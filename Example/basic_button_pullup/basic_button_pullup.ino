// 풀업은 GPIO / GND연결해서 버튼을연결
// INPUT_PULLUP => 버튼이 안눌렸을시 HIGH
const int BUTTON_PIN = 17; // 버튼이 연결된 핀 번호
const int OUTPUT_PIN = 16; // 제어할 출력 핀 번호


int lastButtonState = HIGH; // 이전 버튼 상태 저장
bool outputState = LOW; // 출력 핀 상태 저장
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 입력 풀업 모드 설정
  pinMode(OUTPUT_PIN, OUTPUT); // 출력 핀 모드 설정
  Serial.begin(115200); // 시리얼 통신 시작
  digitalWrite(OUTPUT_PIN, outputState); // 초기 출력 상태 설정
}

void loop() {

  // 기본상태
  // currentButtonState == HIGH
  // lastButtonState == HIGH
  // 버튼이 눌린순간 currentButtonState == LOW로 변함
  int currentButtonState = digitalRead(BUTTON_PIN); // 현재 버튼 상태 읽기
  
  // 버튼 상태 변화 감지
  if (lastButtonState  == HIGH && currentButtonState == LOW) {
    // 출력 상태 토글
    outputState = !outputState;
    digitalWrite(OUTPUT_PIN, outputState); // 출력 핀 상태 변경
    Serial.println("Button Pressed: Output Toggled");
    Serial.print("16번 버튼 상태 : ");
    Serial.println(outputState);
  }

  lastButtonState = currentButtonState; // 현재 상태를 이전 상태로 저장
  delay(50); // 바운싱 방지를 위한 딜레이
}
