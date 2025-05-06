// #include <Wire.h>
// #include "mcp23017.h"
// // "mcp23017.h" 라이브러리를 사용하는방식
// adafruit_mcp23X17라이브러리가 훨씬 편리함

// MCP23017 mcp1, mcp2;

// void setup() {

//   Serial.begin(115200);
//   Wire.begin();

//   Mcp23017_Init(&mcp1, 0x20);
//   Mcp23017_Init(&mcp2, 0x21);

//   // mcp1의 PORTA 출력 / PORTB 입력 설정
//   Set_port_dir(&mcp1, PORTA, MOUTPUT);
//   Set_port_dir(&mcp1, PORTB, MINPUT);
  
//   // mcp2의 PORTA 입력 / PORTB 출력 설정
//   Set_port_dir(&mcp2, PORTA, MINPUT);
//   Set_port_dir(&mcp2, PORTB, MOUTPUT);

// }

// void loop() {
//   Write_gpio(&mcp1, PORTA, 0XFF);
//   Write_gpio(&mcp2, PORTB, 0x00);
//   delay(2000);
//   Set_gpio_pin(&mcp1, PORTA, PIN0, MHIGH);
//   Set_gpio_pin(&mcp1, PORTA, PIN1, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN2, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN3, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN4, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN5, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN6, MLOW);
//   Set_gpio_pin(&mcp1, PORTA, PIN7, MLOW);
//   Set_gpio_pin(&mcp2, PORTB, PIN0, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN1, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN2, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN3, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN4, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN5, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN6, MHIGH);
//   Set_gpio_pin(&mcp2, PORTB, PIN7, MHIGH);
//   delay(2000);
//   // mcp1의 PORTB와 mcp2의 PORTA 값을 읽어와서 시리얼 모니터에 출력
//   unsigned char portb_value = Read_gpio(&mcp1, PORTB);
//   unsigned char porta_value = Read_gpio(&mcp2, PORTA);

//   Serial.println("mcp1의 PORTB 개별 핀 상태:");
//   printPinStates(portb_value);

//   Serial.println("mcp2의 PORTA 개별 핀 상태:");
//   printPinStates(porta_value);

//   Serial.println("============================");
//   delay(1000);
// }

// void printPinStates(unsigned char value) {
//   for (int i = 0; i < 8; i++) {
//     Serial.print("PIN");
//     Serial.print(i);
//     Serial.print(": ");
//     Serial.println((value & (1 << i)) ? "HIGH" : "LOW");
//   }
// }