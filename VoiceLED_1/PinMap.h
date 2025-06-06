// #ifndef PinMap_h
// #define PinMap_h
// #include <avr/io.h>
// //------------------------------------------------------------------------------
// /** struct for mapping digital pins */
// struct pin_map_t {
//   volatile uint8_t* ddr;
//   volatile uint8_t* pin;
//   volatile uint8_t* port;
//   uint8_t bit;
// };
// //------------------------------------------------------------------------------
// #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// // Mega

// // Two Wire (aka I2C) ports
// uint8_t const SDA_PIN = 20;
// uint8_t const SCL_PIN = 21;

// // SPI port
// uint8_t const SS_PIN = 53;
// uint8_t const MOSI_PIN = 51;
// uint8_t const MISO_PIN = 50;
// uint8_t const SCK_PIN = 52;

// static const pin_map_t digitalPinMap[] = {
//   {&DDRE, &PINE, &PORTE, 0},  // E0  0
//   {&DDRE, &PINE, &PORTE, 1},  // E1  1
//   {&DDRE, &PINE, &PORTE, 4},  // E4  2
//   {&DDRE, &PINE, &PORTE, 5},  // E5  3
//   {&DDRG, &PING, &PORTG, 5},  // G5  4
//   {&DDRE, &PINE, &PORTE, 3},  // E3  5
//   {&DDRH, &PINH, &PORTH, 3},  // H3  6
//   {&DDRH, &PINH, &PORTH, 4},  // H4  7
//   {&DDRH, &PINH, &PORTH, 5},  // H5  8
//   {&DDRH, &PINH, &PORTH, 6},  // H6  9
//   {&DDRB, &PINB, &PORTB, 4},  // B4 10
//   {&DDRB, &PINB, &PORTB, 5},  // B5 11
//   {&DDRB, &PINB, &PORTB, 6},  // B6 12
//   {&DDRB, &PINB, &PORTB, 7},  // B7 13
//   {&DDRJ, &PINJ, &PORTJ, 1},  // J1 14
//   {&DDRJ, &PINJ, &PORTJ, 0},  // J0 15
//   {&DDRH, &PINH, &PORTH, 1},  // H1 16
//   {&DDRH, &PINH, &PORTH, 0},  // H0 17
//   {&DDRD, &PIND, &PORTD, 3},  // D3 18
//   {&DDRD, &PIND, &PORTD, 2},  // D2 19
//   {&DDRD, &PIND, &PORTD, 1},  // D1 20
//   {&DDRD, &PIND, &PORTD, 0},  // D0 21
//   {&DDRA, &PINA, &PORTA, 0},  // A0 22
//   {&DDRA, &PINA, &PORTA, 1},  // A1 23
//   {&DDRA, &PINA, &PORTA, 2},  // A2 24
//   {&DDRA, &PINA, &PORTA, 3},  // A3 25
//   {&DDRA, &PINA, &PORTA, 4},  // A4 26
//   {&DDRA, &PINA, &PORTA, 5},  // A5 27
//   {&DDRA, &PINA, &PORTA, 6},  // A6 28
//   {&DDRA, &PINA, &PORTA, 7},  // A7 29
//   {&DDRC, &PINC, &PORTC, 7},  // C7 30
//   {&DDRC, &PINC, &PORTC, 6},  // C6 31
//   {&DDRC, &PINC, &PORTC, 5},  // C5 32
//   {&DDRC, &PINC, &PORTC, 4},  // C4 33
//   {&DDRC, &PINC, &PORTC, 3},  // C3 34
//   {&DDRC, &PINC, &PORTC, 2},  // C2 35
//   {&DDRC, &PINC, &PORTC, 1},  // C1 36
//   {&DDRC, &PINC, &PORTC, 0},  // C0 37
//   {&DDRD, &PIND, &PORTD, 7},  // D7 38
//   {&DDRG, &PING, &PORTG, 2},  // G2 39
//   {&DDRG, &PING, &PORTG, 1},  // G1 40
//   {&DDRG, &PING, &PORTG, 0},  // G0 41
//   {&DDRL, &PINL, &PORTL, 7},  // L7 42
//   {&DDRL, &PINL, &PORTL, 6},  // L6 43
//   {&DDRL, &PINL, &PORTL, 5},  // L5 44
//   {&DDRL, &PINL, &PORTL, 4},  // L4 45
//   {&DDRL, &PINL, &PORTL, 3},  // L3 46
//   {&DDRL, &PINL, &PORTL, 2},  // L2 47
//   {&DDRL, &PINL, &PORTL, 1},  // L1 48
//   {&DDRL, &PINL, &PORTL, 0},  // L0 49
//   {&DDRB, &PINB, &PORTB, 3},  // B3 50
//   {&DDRB, &PINB, &PORTB, 2},  // B2 51
//   {&DDRB, &PINB, &PORTB, 1},  // B1 52
//   {&DDRB, &PINB, &PORTB, 0},  // B0 53
//   {&DDRF, &PINF, &PORTF, 0},  // F0 54
//   {&DDRF, &PINF, &PORTF, 1},  // F1 55
//   {&DDRF, &PINF, &PORTF, 2},  // F2 56
//   {&DDRF, &PINF, &PORTF, 3},  // F3 57
//   {&DDRF, &PINF, &PORTF, 4},  // F4 58
//   {&DDRF, &PINF, &PORTF, 5},  // F5 59
//   {&DDRF, &PINF, &PORTF, 6},  // F6 60
//   {&DDRF, &PINF, &PORTF, 7},  // F7 61
//   {&DDRK, &PINK, &PORTK, 0},  // K0 62
//   {&DDRK, &PINK, &PORTK, 1},  // K1 63
//   {&DDRK, &PINK, &PORTK, 2},  // K2 64
//   {&DDRK, &PINK, &PORTK, 3},  // K3 65
//   {&DDRK, &PINK, &PORTK, 4},  // K4 66
//   {&DDRK, &PINK, &PORTK, 5},  // K5 67
//   {&DDRK, &PINK, &PORTK, 6},  // K6 68
//   {&DDRK, &PINK, &PORTK, 7}   // K7 69
// };
// //------------------------------------------------------------------------------
// #elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
// // Sanguino

// // Two Wire (aka I2C) ports
// uint8_t const SDA_PIN = 17;
// uint8_t const SCL_PIN = 18;

// // SPI port
// uint8_t const SS_PIN = 4;
// uint8_t const MOSI_PIN = 5;
// uint8_t const MISO_PIN = 6;
// uint8_t const SCK_PIN = 7;

// static const pin_map_t digitalPinMap[] = {
//   {&DDRB, &PINB, &PORTB, 0},  // B0  0
//   {&DDRB, &PINB, &PORTB, 1},  // B1  1
//   {&DDRB, &PINB, &PORTB, 2},  // B2  2
//   {&DDRB, &PINB, &PORTB, 3},  // B3  3
//   {&DDRB, &PINB, &PORTB, 4},  // B4  4
//   {&DDRB, &PINB, &PORTB, 5},  // B5  5
//   {&DDRB, &PINB, &PORTB, 6},  // B6  6
//   {&DDRB, &PINB, &PORTB, 7},  // B7  7
//   {&DDRD, &PIND, &PORTD, 0},  // D0  8
//   {&DDRD, &PIND, &PORTD, 1},  // D1  9
//   {&DDRD, &PIND, &PORTD, 2},  // D2 10
//   {&DDRD, &PIND, &PORTD, 3},  // D3 11
//   {&DDRD, &PIND, &PORTD, 4},  // D4 12
//   {&DDRD, &PIND, &PORTD, 5},  // D5 13
//   {&DDRD, &PIND, &PORTD, 6},  // D6 14
//   {&DDRD, &PIND, &PORTD, 7},  // D7 15
//   {&DDRC, &PINC, &PORTC, 0},  // C0 16
//   {&DDRC, &PINC, &PORTC, 1},  // C1 17
//   {&DDRC, &PINC, &PORTC, 2},  // C2 18
//   {&DDRC, &PINC, &PORTC, 3},  // C3 19
//   {&DDRC, &PINC, &PORTC, 4},  // C4 20
//   {&DDRC, &PINC, &PORTC, 5},  // C5 21
//   {&DDRC, &PINC, &PORTC, 6},  // C6 22
//   {&DDRC, &PINC, &PORTC, 7},  // C7 23
//   {&DDRA, &PINA, &PORTA, 7},  // A7 24
//   {&DDRA, &PINA, &PORTA, 6},  // A6 25
//   {&DDRA, &PINA, &PORTA, 5},  // A5 26
//   {&DDRA, &PINA, &PORTA, 4},  // A4 27
//   {&DDRA, &PINA, &PORTA, 3},  // A3 28
//   {&DDRA, &PINA, &PORTA, 2},  // A2 29
//   {&DDRA, &PINA, &PORTA, 1},  // A1 30
//   {&DDRA, &PINA, &PORTA, 0}   // A0 31
// };
// //------------------------------------------------------------------------------
// #elif defined(__AVR_ATmega32U4__)
// // Leonardo
// // Two Wire (aka I2C) ports
// uint8_t const SDA_PIN = 2;
// uint8_t const SCL_PIN = 3;

// // SPI port
// uint8_t const SS_PIN = 17;
// uint8_t const MOSI_PIN = 16;
// uint8_t const MISO_PIN = 14;
// uint8_t const SCK_PIN = 15;

// static const pin_map_t digitalPinMap[] = {
//   {&DDRD, &PIND, &PORTD, 2},  // D2  0
//   {&DDRD, &PIND, &PORTD, 3},  // D3  1
//   {&DDRD, &PIND, &PORTD, 1},  // D1  2
//   {&DDRD, &PIND, &PORTD, 0},  // D0  3
//   {&DDRD, &PIND, &PORTD, 4},  // D4  4
//   {&DDRC, &PINC, &PORTC, 6},  // C6  5
//   {&DDRD, &PIND, &PORTD, 7},  // D7  6
//   {&DDRE, &PINE, &PORTE, 6},  // E6  7
//   {&DDRB, &PINB, &PORTB, 4},  // B4  8
//   {&DDRB, &PINB, &PORTB, 5},  // B5  9
//   {&DDRB, &PINB, &PORTB, 6},  // B6 10
//   {&DDRB, &PINB, &PORTB, 7},  // B7 11
//   {&DDRD, &PIND, &PORTD, 6},  // D6 12
//   {&DDRC, &PINC, &PORTC, 7},  // C7 13
//   {&DDRB, &PINB, &PORTB, 3},  // B3 14
//   {&DDRB, &PINB, &PORTB, 1},  // B1 15
//   {&DDRB, &PINB, &PORTB, 2},  // B2 16
//   {&DDRB, &PINB, &PORTB, 0},  // B0 17
//   {&DDRF, &PINF, &PORTF, 7},  // F7 18
//   {&DDRF, &PINF, &PORTF, 6},  // F6 19
//   {&DDRF, &PINF, &PORTF, 5},  // F5 20
//   {&DDRF, &PINF, &PORTF, 4},  // F4 21
//   {&DDRF, &PINF, &PORTF, 1},  // F1 22
//   {&DDRF, &PINF, &PORTF, 0},  // F0 23
// };
// //------------------------------------------------------------------------------
// #elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
// // Teensy++ 1.0 & 2.0

// // Two Wire (aka I2C) ports
// uint8_t const SDA_PIN = 1;
// uint8_t const SCL_PIN = 0;

// // SPI port
// uint8_t const SS_PIN = 20;
// uint8_t const MOSI_PIN = 22;
// uint8_t const MISO_PIN = 23;
// uint8_t const SCK_PIN = 21;

// static const pin_map_t digitalPinMap[] = {
//   {&DDRD, &PIND, &PORTD, 0},  // D0  0
//   {&DDRD, &PIND, &PORTD, 1},  // D1  1
//   {&DDRD, &PIND, &PORTD, 2},  // D2  2
//   {&DDRD, &PIND, &PORTD, 3},  // D3  3
//   {&DDRD, &PIND, &PORTD, 4},  // D4  4
//   {&DDRD, &PIND, &PORTD, 5},  // D5  5
//   {&DDRD, &PIND, &PORTD, 6},  // D6  6
//   {&DDRD, &PIND, &PORTD, 7},  // D7  7
//   {&DDRE, &PINE, &PORTE, 0},  // E0  8
//   {&DDRE, &PINE, &PORTE, 1},  // E1  9
//   {&DDRC, &PINC, &PORTC, 0},  // C0 10
//   {&DDRC, &PINC, &PORTC, 1},  // C1 11
//   {&DDRC, &PINC, &PORTC, 2},  // C2 12
//   {&DDRC, &PINC, &PORTC, 3},  // C3 13
//   {&DDRC, &PINC, &PORTC, 4},  // C4 14
//   {&DDRC, &PINC, &PORTC, 5},  // C5 15
//   {&DDRC, &PINC, &PORTC, 6},  // C6 16
//   {&DDRC, &PINC, &PORTC, 7},  // C7 17
//   {&DDRE, &PINE, &PORTE, 6},  // E6 18
//   {&DDRE, &PINE, &PORTE, 7},  // E7 19
//   {&DDRB, &PINB, &PORTB, 0},  // B0 20
//   {&DDRB, &PINB, &PORTB, 1},  // B1 21
//   {&DDRB, &PINB, &PORTB, 2},  // B2 22
//   {&DDRB, &PINB, &PORTB, 3},  // B3 23
//   {&DDRB, &PINB, &PORTB, 4},  // B4 24
//   {&DDRB, &PINB, &PORTB, 5},  // B5 25
//   {&DDRB, &PINB, &PORTB, 6},  // B6 26
//   {&DDRB, &PINB, &PORTB, 7},  // B7 27
//   {&DDRA, &PINA, &PORTA, 0},  // A0 28
//   {&DDRA, &PINA, &PORTA, 1},  // A1 29
//   {&DDRA, &PINA, &PORTA, 2},  // A2 30
//   {&DDRA, &PINA, &PORTA, 3},  // A3 31
//   {&DDRA, &PINA, &PORTA, 4},  // A4 32
//   {&DDRA, &PINA, &PORTA, 5},  // A5 33
//   {&DDRA, &PINA, &PORTA, 6},  // A6 34
//   {&DDRA, &PINA, &PORTA, 7},  // A7 35
//   {&DDRE, &PINE, &PORTE, 4},  // E4 36
//   {&DDRE, &PINE, &PORTE, 5},  // E5 37
//   {&DDRF, &PINF, &PORTF, 0},  // F0 38
//   {&DDRF, &PINF, &PORTF, 1},  // F1 39
//   {&DDRF, &PINF, &PORTF, 2},  // F2 40
//   {&DDRF, &PINF, &PORTF, 3},  // F3 41
//   {&DDRF, &PINF, &PORTF, 4},  // F4 42
//   {&DDRF, &PINF, &PORTF, 5},  // F5 43
//   {&DDRF, &PINF, &PORTF, 6},  // F6 44
//   {&DDRF, &PINF, &PORTF, 7}   // F7 45
// };
// //------------------------------------------------------------------------------
// #else  // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// // 168 and 328 Arduinos

// // Two Wire (aka I2C) ports
// uint8_t const SDA_PIN = 18;
// uint8_t const SCL_PIN = 19;

// // SPI port
// uint8_t const SS_PIN = 10;
// uint8_t const MOSI_PIN = 11;
// uint8_t const MISO_PIN = 12;
// uint8_t const SCK_PIN = 13;

// static const pin_map_t digitalPinMap[] = {
//   {&DDRD, &PIND, &PORTD, 0},  // D0  0
//   {&DDRD, &PIND, &PORTD, 1},  // D1  1
//   {&DDRD, &PIND, &PORTD, 2},  // D2  2
//   {&DDRD, &PIND, &PORTD, 3},  // D3  3
//   {&DDRD, &PIND, &PORTD, 4},  // D4  4
//   {&DDRD, &PIND, &PORTD, 5},  // D5  5
//   {&DDRD, &PIND, &PORTD, 6},  // D6  6
//   {&DDRD, &PIND, &PORTD, 7},  // D7  7
//   {&DDRB, &PINB, &PORTB, 0},  // B0  8
//   {&DDRB, &PINB, &PORTB, 1},  // B1  9
//   {&DDRB, &PINB, &PORTB, 2},  // B2 10
//   {&DDRB, &PINB, &PORTB, 3},  // B3 11
//   {&DDRB, &PINB, &PORTB, 4},  // B4 12
//   {&DDRB, &PINB, &PORTB, 5},  // B5 13
//   {&DDRC, &PINC, &PORTC, 0},  // C0 14
//   {&DDRC, &PINC, &PORTC, 1},  // C1 15
//   {&DDRC, &PINC, &PORTC, 2},  // C2 16
//   {&DDRC, &PINC, &PORTC, 3},  // C3 17
//   {&DDRC, &PINC, &PORTC, 4},  // C4 18
//   {&DDRC, &PINC, &PORTC, 5}   // C5 19
// };
// #endif  // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// //------------------------------------------------------------------------------
// static const uint8_t digitalPinCount = sizeof(digitalPinMap)/sizeof(pin_map_t);

// uint8_t badPinNumber(void)
//   __attribute__((error("Pin number is too large or not a constant")));

// static inline __attribute__((always_inline))
//   uint8_t getPinMode(uint8_t pin) {
//   if (__builtin_constant_p(pin) && pin < digitalPinCount) {
//     return (*digitalPinMap[pin].ddr >> digitalPinMap[pin].bit) & 1;
//   } else {
//     return badPinNumber();
//   }
// }
// static inline __attribute__((always_inline))
//   void setPinMode(uint8_t pin, uint8_t mode) {
//   if (__builtin_constant_p(pin) && pin < digitalPinCount) {
//     if (mode) {
//       *digitalPinMap[pin].ddr |= 1 << digitalPinMap[pin].bit;
//     } else {
//       *digitalPinMap[pin].ddr &= ~(1 << digitalPinMap[pin].bit);
//     }
//   } else {
//     badPinNumber();
//   }
// }
// static inline __attribute__((always_inline))
//   uint8_t fastDigitalRead(uint8_t pin) {
//   if (__builtin_constant_p(pin) && pin < digitalPinCount) {
//     return (*digitalPinMap[pin].pin >> digitalPinMap[pin].bit) & 1;
//   } else {
//     return badPinNumber();
//   }
// }
// static inline __attribute__((always_inline))
//   void fastDigitalWrite(uint8_t pin, uint8_t value) {
//   if (__builtin_constant_p(pin) && pin < digitalPinCount) {
//     if (value) {
//       *digitalPinMap[pin].port |= 1 << digitalPinMap[pin].bit;
//     } else {
//       *digitalPinMap[pin].port &= ~(1 << digitalPinMap[pin].bit);
//     }
//   } else {
//     badPinNumber();
//   }
// }
// #endif  // Sd2PinMap_h
