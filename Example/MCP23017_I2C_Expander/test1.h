/*  1초마다 모든 PA, PB핀 출력 ON/OFF
basic_mcp23017.cpp / .h


example : https://github.com/seengreat/MCP23017-SG-IO-E017/blob/main/Arduino/mcp23017/mcp23017.ino
 * Project  :
 * Experimental Platform :Arduino UNO + MCP23017 IO Expansion Module
 * Hardware Connection :Arduino UNO -> MCP23017 IO Expansion Module in wiringpi number
 *    5V --> VCC
 *    GND  --> GND
 *    SDA --> SDA 
 *    SCL --> SCL
 *    D2   --> INTA
 *    D3   --> INTB
 * Author  : Andy Li
 * Web Site  : www.seengreat.com


// mcp23017.ino
#include <Wire.h>
#include "mcp23017.h"
#define PIN_INTA   32
#define PIN_INTB   33


void setup(){
   Serial.begin(115200);
   Wire.begin();
   
  //  pinMode(PIN_INTA, INPUT_PULLUP);
  //  pinMode(PIN_INTB, INPUT_PULLUP);
  //  attachInterrupt(PIN_INTB, Int_callback, CHANGE);
   
   Mcp23017_Init();
   Set_port_dir(PORTA, MOUTPUT);//config PORTA as output
   Set_port_dir(PORTB, MINPUT);//config PORTA as input
   Set_io_pu(PORTB, PIN_ALL, ENABLE);//PORTB enable pullup
   //Set the interrupt mode of all pins of PORTB port to level change
   Set_io_int(PORTB, PIN7, INT_CHANGE_LEVEL);
   Serial.printf("INTCAP portB:%02x\r\n",Read_intcap(PORTB));
   // put your setup code here, to run once:
   Serial.printf("read portB:%02x\r\n",Read_gpio(PORTB));
}

void loop(){
    Serial.printf("port A ouput high\r\n");
    //Set_gpio_pin(PORTA, PIN4, MHIGH)
    Write_gpio(PORTA, 0XFF);
    Serial.printf("portA:%02x\r\n",Read_gpio(PORTA));

    delay(1000);
    Serial.printf("port A ouput low\r\n");
    //Set_gpio_pin(PORTA, PIN4, MLOW);
    Write_gpio(PORTA, 0X00);
    Serial.printf("portA:%02x\r\n",Read_gpio(PORTA));
    delay(1000);

}


*/