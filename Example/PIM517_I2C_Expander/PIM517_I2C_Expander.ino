#include <Wire.h>
#include <IOExpander.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define IO_EXPANDER_ADDR 0x18
#define ANALOG_PIN 12

IOExpander ioe(Wire, IO_EXPANDER_ADDR);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!ioe.initialise()) {
    Serial.println("IO Expander 초기화 실패!");
    while (1);
  }

  ioe.setAdcVref(3.3f);  // IO Expander의 입력 전압, Breakout Garden에서는 3.3V
  ioe.setMode(ANALOG_PIN, IOExpander::PIN_ADC);
}

void loop() {
  float voltage = ioe.inputAsVoltage(ANALOG_PIN);
  Serial.print("아날로그 입력 전압: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  delay(100);
}