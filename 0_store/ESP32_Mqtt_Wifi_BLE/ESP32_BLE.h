#ifndef ESP32_BLE_H
#define ESP32_BLE_H

#include <NimBLEDevice.h>

// 외부에서 TX 특성에 접근할 수 있도록 선언
extern NimBLECharacteristic* pTxCharacteristic;

// BLE 초기화 및 광고 시작
void setBLE();

#endif // ESP32_BLE_H
