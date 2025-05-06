const int FLOW_SENSOR_PIN = 14; // 유량계 센서를 연결한 ESP32의 GPIO 핀 번호
volatile int pulseCount = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

void IRAM_ATTR pulseCounter(){
  pulseCount++;
}

void setup(){
  Serial.begin(115200);
  
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
  
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  oldTime = 0;
}

void loop()
{
  if((millis() - oldTime) > 1000)    // 1초마다 계산 업데이트
  {
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));
        
    // 유량 계산
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / 38; // S402B의 K-Factor를 5.5로 가정
    
    // 리터 단위로 변환
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // 총 유량 누적
    totalMilliLitres += flowMilliLitres;
    
    // 결과 출력
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.print("L/min");
    Serial.print("\t");

    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");

    // 변수 초기화
    pulseCount = 0;
    oldTime = millis();
    
    // 인터럽트 다시 활성화
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
  }
}