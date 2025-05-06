#include <Wire.h>

#define MLX90614_DEFAULT_ADDRESS 0x5A
#define MLX90614_SMBUS_ADDR      0x0E | 0x20

uint8_t crc8Polyomial107(uint8_t* ptr, uint8_t len) {
  uint8_t i;
  uint8_t crc = 0x00;

  while (len--) {
    crc ^= *ptr++;
    for (i = 8; i > 0; i--) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x07;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}

void writeReg(uint8_t reg, uint8_t* buf) {
  uint8_t crc_write[5] = { (uint8_t)(MLX90614_DEFAULT_ADDRESS << 1), reg, buf[0], buf[1], 0x00 };

  Wire.beginTransmission(MLX90614_DEFAULT_ADDRESS);
  Wire.write(reg);
  Wire.write(buf, 2);
  Wire.write(crc8Polyomial107(crc_write, 4));
  Wire.endTransmission();
}

uint8_t readReg(uint8_t reg, uint8_t* buf) {
  uint8_t crc_read[6] = { (uint8_t)(MLX90614_DEFAULT_ADDRESS << 1), reg, (uint8_t)((MLX90614_DEFAULT_ADDRESS << 1) | 1), 0x00, 0x00, 0x00 };
  uint8_t pec = 0;

  Wire.beginTransmission(MLX90614_DEFAULT_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(MLX90614_DEFAULT_ADDRESS, (uint8_t)3);
  uint8_t i = 0;
  while (Wire.available()) {
    if (i < 2) {
      buf[i] = Wire.read();
      crc_read[3 + i] = buf[i];
    } else {
      pec = Wire.read();
    }
    i++;
  }
  Wire.endTransmission();

  if (pec != crc8Polyomial107(crc_read, 5)) {
    return 0;
  }
  return 1;
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("=========================================");
  Serial.println("=========================================");
  
  // MLX90614의 현재 I2C 주소 확인
  uint8_t currentAddress = 0;
  uint8_t buf[2] = {0};
  if (readReg(MLX90614_SMBUS_ADDR, buf)) {
    currentAddress = buf[0];
    Serial.print("Current I2C address: 0x");
    Serial.println(currentAddress, HEX);
  } else {
    Serial.println("Failed to read current address");
  }
  
  // 새로운 I2C 주소로 변경 (예: 0x3A)
  uint8_t newAddress = 0x3A;
  buf[0] = newAddress;
  buf[1] = 0x00;
  writeReg(MLX90614_SMBUS_ADDR, buf);
  
  delay(50); // EEPROM 쓰기 완료까지 대기
  
  // 변경된 I2C 주소 확인
  if (readReg(MLX90614_SMBUS_ADDR, buf)) {
    currentAddress = buf[0];
    Serial.print("New I2C address: 0x");
    Serial.println(currentAddress, HEX);
  } else {
    Serial.println("Failed to read new address");
  }
}

void loop() {
  // 메인 루프에서 수행할 작업 추가
}