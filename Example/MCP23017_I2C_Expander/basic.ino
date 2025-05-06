/*
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

*/
/*
#include <string.h>
#include <stdlib.h> 
#include <Wire.h>
#include "mcp23017.h"

//Configure the serial port to use the standard printf function
//start
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}
//end
volatile int int_flag=0;
//Interrupt service function triggered by interrupt pin
void Int_callback()
{
    int_flag = 1;
}

void setup() 
{
   Serial.begin(115200);
   printf_begin();
   Wire.begin();
   
   attachInterrupt(digitalPinToInterrupt(PIN_INTB), Int_callback, CHANGE); //int0-->D2  int1--> D3
   
   Mcp23017_Init();
   Set_port_dir(PORTA, MOUTPUT);//config PORTA as output
   Set_port_dir(PORTB, MINPUT);//config PORTA as input
   Set_io_pu(PORTB, PIN_ALL, ENABLE);//PORTB enable pullup
   //Set the interrupt mode of all pins of PORTB port to level change
   Set_io_int(PORTB, PIN7, INT_CHANGE_LEVEL);
   printf("INTCAP portB:%02x\r\n",Read_intcap(PORTB));
   // put your setup code here, to run once:
   printf("read portB:%02x\r\n",Read_gpio(PORTB));

}

void loop() 
{
    printf("port A ouput high\r\n");
    //Set_gpio_pin(PORTA, PIN4, MHIGH)
    Write_gpio(PORTA, 0XFF);
    printf("portA:%02x\r\n",Read_gpio(PORTA));
    if(int_flag == 1)
    {
        printf("ISR read portB:%02x\r\n",Read_gpio(PORTB));
        int_flag = 0;
    }
    delay(1000);
    printf("port A ouput low\r\n");
    //Set_gpio_pin(PORTA, PIN4, MLOW);
    Write_gpio(PORTA, 0X00);
    printf("portA:%02x\r\n",Read_gpio(PORTA));
    if(int_flag == 1)
    {
        printf("ISR read portB:%02x\r\n",Read_gpio(PORTB));
        int_flag = 0;
    }
    delay(1000);

}
*/