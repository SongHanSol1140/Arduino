#include <Wire.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp7;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!mcp1.begin_I2C(0x20)) {
    Serial.println("MCP23017 1 not found");
    while (1);
      
  }

  if (!mcp2.begin_I2C(0x21)) {
    Serial.println("MCP23017 2 not found");
    while (1);
      
  }

  // mcp1의 PORTA 출력 / PORTB 입력 설정
  for (int i = 0; i < 8; i++) {
    mcp1.pinMode(i, OUTPUT);
    mcp1.pinMode(i + 8, INPUT_PULLUP);
  }

  // mcp2의 PORTA 입력 / PORTB 출력 설정
  for (int i = 0; i < 8; i++) {
    mcp2.pinMode(i, INPUT_PULLUP);
    mcp2.pinMode(i + 8, OUTPUT);
  }


  // MCP1 PORTA를 모두 HIGH로 설정
  mcp1.writeGPIOA(0xFF);
  // MCP2 PORTB를 모두 LOW로 설정
  mcp2.writeGPIOB(0x00);
  delay(2000);

  // MCP1 PORTA의 개별 핀 설정
  mcp1.digitalWrite(0, HIGH);
  mcp1.digitalWrite(1, LOW);
  mcp1.digitalWrite(2, HIGH);
  mcp1.digitalWrite(3, LOW);
  mcp1.digitalWrite(4, HIGH);
  mcp1.digitalWrite(5, LOW);
  mcp1.digitalWrite(6, HIGH);
  mcp1.digitalWrite(7, LOW);
  

  // MCP2 PORTB의 개별 핀 설정
  for (int i = 8; i < 16; i++) {
    mcp2.digitalWrite(i, HIGH);
  }
  delay(2000);
}

void loop() {

  // mcp1의 PORTB와 mcp2의 PORTA 값을 읽어와서 시리얼 모니터에 출력
  uint8_t portb_value = mcp1.readGPIOB();
  uint8_t porta_value = mcp2.readGPIOA();
  bool pa4_state = mcp1.digitalRead(4);

  Serial.print("mcp1의 PA0 핀 상태: ");
  Serial.println(mcp1.digitalRead(0));
  Serial.print("mcp1의 PA1 핀 상태: ");
  Serial.println(mcp1.digitalRead(1));
  Serial.print("mcp1의 PA2 핀 상태: ");
  Serial.println(mcp1.digitalRead(2));
  Serial.print("mcp1의 PA3 핀 상태: ");
  Serial.println(mcp1.digitalRead(3));
  Serial.print("mcp1의 PA4 핀 상태: ");
  Serial.println(mcp1.digitalRead(4));
  Serial.print("mcp1의 PA5 핀 상태: ");
  Serial.println(mcp1.digitalRead(5));
  Serial.print("mcp1의 PA6 핀 상태: ");
  Serial.println(mcp1.digitalRead(6));
  Serial.print("mcp1의 PA7 핀 상태: ");
  Serial.println(mcp1.digitalRead(7));
  Serial.println("mcp1의 PORTB 개별 핀 상태:");
  Serial.println(portb_value);
  printPinStates(portb_value);

  Serial.println("mcp2의 PORTA 개별 핀 상태:");
  Serial.println(porta_value);
  printPinStates(porta_value);

  Serial.println("============================");
  delay(1000);
}

void printPinStates(uint8_t value) {
  for (int i = 0; i < 8; i++) {
    Serial.print("PIN");
    Serial.print(i);
    Serial.print(": ");
    Serial.println((value & (1 << i)) ? "HIGH" : "LOW");
    
  }
}