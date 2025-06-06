/*!
 * @file        setSensor.ino
 * @brief       this demo is to set the emissivity calibration coefficient, and set measurement parameters, including IIR, FIR and measurement objects
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [qsjhyy](yihuan.huang@dfrobot.com)
 * @version     V1.0
 * @date        2021-08-09
 * @url         https://github.com/DFRobot/DFRobot_MLX90614
 */
#include <DFRobot_MLX90614.h>
// 기존 I2C Address(미설정시 기본주소는 0x5A)
// getData로
const uint8_t MLX90614_I2C_ADDR = 0x5A;
// 바꿀 I2C Adress
const uint8_t MLX90614_I2C_ChangeADDR = 0x5D;
const int SDA_PIN = 21;
const int SCL_PIN = 22;

// DFRobot_MLX90614_I2C sensor(MLX90614_I2C_ADDR, &Wire);   // instantiate an object to drive the sensor
DFRobot_MLX90614_I2C sensor(/*uint8_t i2cAddr=*/MLX90614_I2C_ADDR, /*TwoWire *pWire = */&Wire, /*int sdaPin=*/SDA_PIN, /*int sclPin=*/SCL_PIN);
void setup(){
  Serial.begin(115200);
  // initialize the sensor
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * set the emissivity calibration coefficient, users need to calculate the ratio of the temperature measured before the sensor changes emissivity to the true temperature of the object,
   * upload the ratio to the api as a parameter, and the deviation of the object absolute temperature measured by the sensor will be lower
   * calibrationValue new calibration coefficient, [0.1, 1.0]
   * Not applicable to the mlx90614 Series c
   */
  sensor.setEmissivityCorrectionCoefficient(1.0);

  /**
   * set I2C communication address, the setting takes effect after power down and restart
   * addr new I2C communication address 7bit(0~127)
   */
  sensor.setI2CAddress(MLX90614_I2C_ChangeADDR);

  /**
   * set the measurement parameters, including IIR (Infinite Impulse Response Digital Filter) and FIR (Finite Impulse Response Digital Filter)
   * IIRMode: eIIR100, eIIR80, eIIR67, eIIR57;
   * FIRMode: eFIR128, eFIR256, eFIR512, eFIR1024;
   */
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);

  /**
   * control the sensor sleep mode, must enter and exit the sleep mode once after the sensor is configured (equivalent to soft reset) to ensure the normal reading of the measured data
   * mode select to enter or exit sleep mode, it's enter sleep mode by default
   *      true put the sensor to sleep
   *      false wake up the sensor (automatically exit sleep mode after power down and restart)
   */
  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);
}

void loop(){
  // /**
  //  * get ambient temperature, unit is Celsius
  //  * return value range： -40.01 °C ~ 85 °C
  //  */
  // float ambientTemp = sensor.getAmbientTempCelsius();

  // /**
  //  * get temperature of object 1, unit is Celsius
  //  * return value range： 
  //  * @n  -70.01 °C ~ 270 °C(MLX90614ESF-DCI)
  //  * @n  -70.01 °C ~ 380 °C(MLX90614ESF-DCC)
  //  */
  // float objectTemp = sensor.getObjectTempCelsius();

  // // print measured data in Celsius, unit is Celsius (°C)
  // Serial.print("Ambient celsius : "); Serial.print(ambientTemp); Serial.println(" °C");
  // Serial.print("Object celsius : ");  Serial.print(objectTemp);  Serial.println(" °C");

  // // print measured data in Fahrenheit, unit is Fahrenheit (F)
  // Serial.print("Ambient fahrenheit : "); Serial.print(ambientTemp*9/5 + 32); Serial.println(" F");
  // Serial.print("Object fahrenheit : ");  Serial.print(objectTemp*9/5 + 32);  Serial.println(" F");

  // Serial.println();
  Serial.println("Need ReConnected Vcc");
  
  delay(1000);
}

