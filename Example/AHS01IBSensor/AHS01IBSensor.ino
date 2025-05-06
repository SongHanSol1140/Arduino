#include <Wire.h>

#define AHS01IB_I2C_ADDRESS 0x15

void setup() {
  Serial.begin(115200);
  // EPS32의 경우 I2C통신을 위해 22번핀 SCL / 21번핀 SDA이 기본으로 설정되어있음
  Wire.begin();
  startMeasurement();
}

void loop() {
  float humidity = readHumidity();
  Serial.print("현재 습도: ");
  Serial.print(humidity);
  Serial.println("%");
  delay(500); // Read every second
}

void startMeasurement() {
  Wire.beginTransmission(AHS01IB_I2C_ADDRESS);
  Wire.write(0x06); // Start command MSB
  Wire.write(0x01); // Start command LSB
  Wire.endTransmission();
}

float readHumidity() {
  Wire.beginTransmission(AHS01IB_I2C_ADDRESS);
  Wire.write(0x00); // command MSB
  Wire.write(0x02); // command LSB
  Wire.endTransmission();

  Wire.requestFrom(AHS01IB_I2C_ADDRESS, 2);
  while (Wire.available() < 2);

  uint8_t msb = Wire.read(); // 상위 비트 => 1은 16*16 = 256을 의미
  uint8_t lsb = Wire.read(); // 하위 비트 1 ~ 255
  Serial.print("msb: ");
  Serial.println(msb);
  Serial.print("lsb: ");
  Serial.println(lsb);

  float humidity = ((msb << 8) | lsb) / 10.0;
  return humidity;
}
// msb: 1
// lsb: 15
// 현재 습도: 27.10%
// msb 1(256) + 15 = 271 / 10 = 27.1%

void endMeasurement() {
  Wire.beginTransmission(AHS01IB_I2C_ADDRESS);
  Wire.write(0x07); // command MSB
  Wire.write(0x01); // command LSB
  Wire.endTransmission();
}
