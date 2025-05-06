// #include <string.h>
// #include <stdlib.h> 
// #include <Wire.h>
// #include "mcp23017.h"

// static void Write_reg(uint8_t address, unsigned char reg, unsigned char value)
// {
//     Wire.beginTransmission(address);
//     Wire.write(reg);
//     Wire.write(value);
//     Wire.endTransmission();
// }

// static unsigned char Read_reg(uint8_t address, unsigned char reg)
// {
//     Wire.beginTransmission(address);
//     Wire.write(reg);
//     Wire.endTransmission();
//     Wire.requestFrom(address, 1);
//     return Wire.read();
// }

// void Mcp23017_Init(MCP23017* mcp, uint8_t address)
// {
//     mcp->address = address;
//     pinMode(PIN_INTA, INPUT_PULLUP);  //INTA
//     pinMode(PIN_INTB, INPUT_PULLUP);  //INTB
// }

// void Set_port_dir(MCP23017* mcp, unsigned char port, unsigned char port_dir)
// {
//     if (port_dir == MINPUT)
//         Write_reg(mcp->address, IODIR+port, 0xFF);
//     else if (port_dir == MOUTPUT)
//         Write_reg(mcp->address, IODIR+port, 0x00);
// }

// unsigned char Set_io_dir(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char pin_dir)
// {
//     unsigned char state;
//     state = Read_reg(mcp->address, IODIR+port);
//     if (pin_dir == MINPUT)
//     {
//         state |= pin;
//     }
//     else if (pin_dir == MOUTPUT)
//     {
//         state &= ~pin;
//     }
//     else 
//     {
//         Serial.println("dir error!");
//         return 0;
//     }
//     Write_reg(mcp->address, IODIR+port, state);
//     return 1;
// }

// unsigned char Set_io_pu(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char pu)
// {
//     unsigned char state;    
//     state = Read_reg(mcp->address, GPPU+port);
//     if (pu == ENABLE)
//     {
//         state |= pin;
//     }
//     else if (pu == DISABLE)
//     {
//         state &= ~pin;
//     }
//     else
//     {
//         Serial.println("pu state error!");
//         return 0;
//     }
//     Write_reg(mcp->address, GPPU+port, state);
//     return 1;
// }

// unsigned char Set_io_polarty(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char polarity)
// {
//     unsigned char state;
//     state = Read_reg(mcp->address, IPOL + port);
//     if (polarity == ENABLE)
//         state |= pin;
//     else if (polarity == DISABLE)
//         state &= ~pin;
//     else
//     {
//         Serial.println("polarity state error!");
//         return 0;
//     }
//     Write_reg(mcp->address, IPOL + port, state);
//     return 1;
// }

// void Set_io_int(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char int_type)
// {
//     unsigned char inten_state;
//     unsigned char defval_state;
//     unsigned char intcon_state;
//     inten_state = Read_reg(mcp->address, GPINTEN + port);
//     defval_state = Read_reg(mcp->address, DEFVAL + port);
//     intcon_state = Read_reg(mcp->address, INTCON + port);
//     if (int_type == INT_DISABLE)
//     {
//         inten_state &= ~pin;
//     }
//     else if (int_type == INT_HIGH_LEVEL)
//     {
//         inten_state |= pin;
//         defval_state &= ~pin;
//         intcon_state |= pin;
//     }
//     else if (int_type == INT_LOW_LEVEL)
//     {
//         inten_state |= pin;
//         defval_state |= pin;
//         intcon_state |= pin;
//     }
//     else if (int_type == INT_CHANGE_LEVEL)
//     {
//         inten_state |= pin;
//         intcon_state &= ~pin;
//     }
//     Write_reg(mcp->address, GPINTEN + port, inten_state);
//     Write_reg(mcp->address, DEFVAL + port, defval_state);
//     Write_reg(mcp->address, INTCON + port, intcon_state);
// }

// unsigned char Read_intf(MCP23017* mcp, unsigned char port)
// {
//     return Read_reg(mcp->address, INTF + port);
// }

// unsigned char Read_intcap(MCP23017* mcp, unsigned char port)
// {
//     return Read_reg(mcp->address, INTCAP + port);
// }

// unsigned char Read_gpio(MCP23017* mcp, unsigned char port)
// {
//     return Read_reg(mcp->address, GPIO + port);
// }

// unsigned char Read_olat(MCP23017* mcp, unsigned char port)
// {
//     return Read_reg(mcp->address, OLAT + port);
// } 

// void Write_gpio(MCP23017* mcp, unsigned char port, unsigned char value)
// {
//     Write_reg(mcp->address, GPIO + port, value);
// }

// void Set_gpio_pin(MCP23017* mcp, unsigned char port, unsigned char pin, unsigned char value)
// {
//     unsigned char gpio_state;
//     gpio_state = Read_reg(mcp->address, GPIO + port);
//     if (value == MHIGH)
//         gpio_state |= pin;
//     else if (value == MLOW)
//         gpio_state &= ~pin;
//     Write_reg(mcp->address, GPIO + port, gpio_state);
// }