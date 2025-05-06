#include <Wire.h>
#include <PIM517.h>
#include <Adafruit_MCP23X17.h>

#define SDA_PIN 21
#define SCL_PIN 22
// PIN517
const uint8_t PIM517_ADDRESS = 0x18;
int PIN517_PIN7 = 7;
int PIN517_PIN9 = 9;


// MCP23017
const uint8_t MCP23017_ADDRESS = 0x20;
// Arduino Adafruit MCP23X17 Library download
Adafruit_MCP23X17 mcp23017;
IOExpander pim517(Wire, PIM517_ADDRESS);



void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);


  //MCP23017
  if (!mcp23017.begin_I2C(MCP23017_ADDRESS)) {
    Serial.println("MCP23017 Expander not found");
    // while(1);
  }
  // PORTA 출력 / PORTB 입력 설정
  for (int i = 0; i < 8; i++) {
    mcp23017.pinMode(i, OUTPUT);
    mcp23017.pinMode(i + 8, INPUT_PULLUP);
  }
  // 모두 HIGH / Low로 설정
  mcp23017.writeGPIOA(0xFF); // HIGH
  mcp23017.writeGPIOB(0x00); // LOW
  // PA0 / PA1 LOW
  mcp23017.digitalWrite(0, LOW);
  mcp23017.digitalWrite(1, LOW);




  //PIM517
  if (!pim517.initialise()) {
    Serial.println("PIM517 Expander not found");
    // while(1);
  }
  pim517.setAdcVref(3.3f);  // PIM517 IO Expander의 입력 전압
  pim517.setMode(PIN517_PIN7, IOExpander::PIN_ADC);
  pim517.setMode(PIN517_PIN9, IOExpander::PIN_ADC);

  delay(2000);
}

void loop() {
  // MCP 23017
  // PIM517
  float pin7_voltage = pim517.inputAsVoltage(PIN517_PIN7);
  float pin9_voltage = pim517.inputAsVoltage(PIN517_PIN9);
  Serial.print("아날로그 입력 전압 PIN 7 : ");
  Serial.print(pin7_voltage, 2);
  Serial.println(" V");
  Serial.print("아날로그 입력 전압 PIN 9 : ");
  Serial.print(pin9_voltage, 2);
  Serial.println(" V");
  Serial.print("MCP23017 PB0 핀 상태: ");
  Serial.println(mcp23017.digitalRead(8));
  Serial.print("MCP23017 PB1 핀 상태: ");
  Serial.println(mcp23017.digitalRead(9));
  delay(100);
}