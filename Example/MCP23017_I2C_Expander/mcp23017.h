// /********************************************
// 0 1 0  0 A2 A1 A0 
// 0 1 0  0 0  0  0    0x20
// 0 1 0  0 0  0  1    0x21
// 0 1 0  0 0  1  0    0x22
// 0 1 0  0 0  1  1    0x23
// 0 1 0  0 1  0  0    0x24
// 0 1 0  0 1  0  1    0x25
// 0 1 0  0 1  1  0    0x26
// 0 1 0  0 1  1  1    0x27
// *********************************************/

// // mcp23017.h
// #ifndef  __MCP23017_H_
// #define  __MCP23017_H_


// #include <stdio.h>
// #include <stdbool.h>
// #include <stdint.h>
// #include <Arduino.h>

// #ifdef __cplusplus
//  extern "C" {
// #endif

// // CONTROL REGISTER in Sequential mode IOCON.BANK = 0
// // The following registers correspond to port A,
// // +1 for registers corresponding to port B
// #define IODIR     0x00
// #define IPOL      0x02
// #define GPINTEN   0x04
// #define DEFVAL    0X06
// #define INTCON    0x08
// #define IOCON     0x0A
// #define GPPU      0x0C
// #define INTF      0x0E
// #define INTCAP    0x10
// #define GPIO      0x12
// #define OLAT      0x14

// //state definition
// #define MINPUT      0x01
// #define MOUTPUT     0x00
// //port definition
// #define PORTA      0x00
// #define PORTB      0x01

// //pin number definition
// #define PIN0       0x01
// #define PIN1       0x02
// #define PIN2       0x04
// #define PIN3       0x08
// #define PIN4       0x10
// #define PIN5       0x20
// #define PIN6       0x40
// #define PIN7       0x80
// #define PIN_ALL    0xFF

// #define ENABLE     0x01
// #define DISABLE    0x00

// #define POLARITY_REV   0x01
// #define POLARITY_NREV  0x00

// #define MHIGH  0x01
// #define MLOW   0x00

// // INTERRUPT type definition
// #define INT_DISABLE        0x00
// #define INT_HIGH_LEVEL     0x01
// #define INT_LOW_LEVEL      0x02
// #define INT_CHANGE_LEVEL   0x03

// //Define whether INTA and INTB are associated
// #define INTAB_CONJUNCTION  0x00
// #define INTAB_INDEPENDENT  0x01

// // Define the output type of INTA and INTB pins
// #define INT_OD             0x00
// #define INT_PUSHPULL_HIGH  0x01
// #define INT_PUSHPULL_LOW   0x02

// //INTA/B pin wiring to Arduin0 mega 
// //INTA --> P0
// //INTB --> P1
// #define PIN_INTA   2 //int0
// #define PIN_INTB   3 //int1
// // Module use I2C bus,the slave device address setting:

// // default slave I2C interface device is 0x27(A2=1,A1=1,A0=1)
// #define DEV_ADDR  0x20
// typedef struct {
//     uint8_t address;
// } MCP23017;

// void Mcp23017_Init(MCP23017* mcp, uint8_t address);
// void Set_port_dir(MCP23017* mcp, unsigned char port, unsigned char port_dir);
// unsigned char Set_io_dir(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char pin_dir);
// unsigned char Set_io_pu(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char pu);
// unsigned char Set_io_polarty(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char polarity);
// void Set_io_int(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char int_type);
// unsigned char Read_intf(MCP23017* mcp, unsigned char port);
// unsigned char Read_intcap(MCP23017* mcp, unsigned char port);
// unsigned char Read_gpio(MCP23017* mcp, unsigned char port);
// unsigned char Read_olat(MCP23017* mcp, unsigned char port);
// void Write_gpio(MCP23017* mcp, unsigned char port, unsigned char value);
// void Set_gpio_pin(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char value);

// #ifdef __cplusplus
// }
// #endif

// #endif