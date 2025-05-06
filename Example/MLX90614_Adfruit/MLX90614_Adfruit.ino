#include <Wire.h>
#include <Adafruit_MLX90614.h>

// MLX90614 객체 생성q
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mlx.begin(0x5D); // => i2c 주소 삽입 
}

void loop() {
  // 센서에서 온도 읽기
  double ambientTemp = mlx.readAmbientTempC();
  double objectTemp = mlx.readObjectTempC();
  
  // 시리얼 모니터에 출력
  Serial.print("Ambient Temperature: ");
  Serial.print(ambientTemp);
  Serial.println(" *C");

  Serial.print("Object Temperature: ");
  Serial.print(objectTemp);
  Serial.println(" *C");
  
  delay(1000);
}
