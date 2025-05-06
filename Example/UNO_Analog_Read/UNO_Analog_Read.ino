const int numReadings = 1;   // 이동 평균을 위한 읽기 수 (10개)
float readings[numReadings];  // 읽기 값을 저장할 배열
int readIndex = 0;            // 현재 읽기 인덱스
float total = 0.0f;           // 평균 계산을 위한 총합
float average = 0.0f;         // 이동 평균 값
float currentvalue = 0.0f;    // 현재 표시 변수 (전류 값)
float AcsValue = 0.0f;        // 현재 읽기 변수 (아날로그 값)

void setup() {
  Serial.begin(115200);
  
  // 모든 읽기 값을 0으로 초기화
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // 아날로그 핀 A0에서 현재 값 읽기
  AcsValue = analogRead(A0);

  // 이동 평균 계산
  average = calculateMovingAverage(AcsValue);

  // 아날로그 값을 전압(mV)으로 변환
  float voltage_mV = average * (5000.0 / 1023.0);  // 0~1023 값을 0~5000mV로 변환
  
  // 예제에서 주어진 대로 전류 값을 계산 (전류 계산은 사용된 센서에 따라 다를 수 있음)
  currentvalue = (voltage_mV / 1000.0); // 전압을 V 단위로 변환
  
  // 이동 평균으로 계산된 전압 값과 전류 값 출력
  Serial.print("이동 평균 전압 (10개): ");
  Serial.print(voltage_mV);  // mV 단위로 출력
  Serial.print(" mV\t");   // mV 단위 표시 후 탭으로 구분
  Serial.print(currentvalue);  // currentvalue 출력 (전압 값 V 단위)
  Serial.println(" V");   // V 단위 표시
  delay(10);  // 10ms 지연
}

// 이동 평균을 계산하는 함수
float calculateMovingAverage(float newValue) {
  // 총합에서 가장 오래된 읽기 값을 빼기
  total = total - readings[readIndex];
  
  // 새로운 읽기 값을 배열에 추가
  readings[readIndex] = newValue;
  
  // 총합에 새로운 읽기 값을 더하기
  total = total + readings[readIndex];
  
  // 배열의 다음 위치로 인덱스 이동
  readIndex = (readIndex + 1) % numReadings;

  // 이동 평균 계산 및 반환
  return total / numReadings;
}
