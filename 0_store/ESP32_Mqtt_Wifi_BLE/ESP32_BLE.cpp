#include "ESP32_BLE.h"
#include <Arduino.h>

// --- UUID 정의 ---
static const char* SERVICE_UUID           = "12345678-1234-1234-1234-abcdef000000";
static const char* CHARACTERISTIC_UUID_RX = "12345678-1234-1234-1234-0123456789aa";
static const char* CHARACTERISTIC_UUID_TX = "12345678-1234-1234-1234-0123456789bb";

// 전역 핸들러
NimBLEAdvertising*    pAdvertising;
NimBLECharacteristic* pTxCharacteristic;

// RX 쓰기 콜백: 값을 받으면 pTxCharacteristic 으로 응답 노티파이
class MyCharacteristicCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pChr, NimBLEConnInfo &connInfo) override {
    std::string v = pChr->getValue();
    if (v.length()) {
      char c = v[0];
      std::string resp;
      if      (c == '1') resp = "11";
      else if (c == '2') resp = "22";
      else if (c == '3') resp = "33";
      else               resp = "??";
      pTxCharacteristic->setValue(resp);
      pTxCharacteristic->notify();
      Serial.printf("▶ Received %c → Notified %s\n", c, resp.c_str());
    }
  }
};

// 서버 연결/해제 콜백: 연결 상태 로깅 + 광고 재시작
class MyServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo) override {
    Serial.println("▶ Client connected");
  }
  void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason) override {
    Serial.println("◀ Client disconnected, restarting advertising");
    delay(100); // 짧은 지연 추가 (필요에 따라 조절)
    pAdvertising->start();
  }
};

void setBLE() {
  // 1) NimBLE 초기화
  NimBLEDevice::init("peripheral_esp32_1");
  NimBLEDevice::setSecurityAuth(true, true, true);

  // 2) GATT 서버 생성
  NimBLEServer* pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 3) 서비스 & 특성 정의
  NimBLEService* pService = pServer->createService(SERVICE_UUID);

  // TX 특성: Notify + Read
  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ
  );

  // RX 특성: Write
  NimBLECharacteristic* pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    NIMBLE_PROPERTY::WRITE
  );
  pRxCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  pService->start();

  // 4) 광고 시작
  pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
  Serial.println("BLE Advertising Started");
}
