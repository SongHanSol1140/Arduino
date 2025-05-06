#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// UUIDs
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914a"
#define SERVICE_UUID2       "abcdef01-2345-6789-abcd-ef0123456789" // 추가 UUID

void setup() {
  Serial.begin(115200);

  // BLE 디바이스 초기화
  BLEDevice::init("ESP32_BLE_TEST");
  BLEServer *pServer = BLEDevice::createServer();

  // 첫 번째 서비스 생성 및 시작
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pService->start();

  // 두 번째 서비스 생성 및 시작 (선택적)
  BLEService *pService2 = pServer->createService(SERVICE_UUID2);
  pService2->start();

  // BLE 광고 시작
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_UUID2); // 여기에 추가 UUID를 포함
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  Serial.println("BLE 광고 시작");
  Serial.print("광고 중인 UUID1: ");
  Serial.println(SERVICE_UUID);
  Serial.print("광고 중인 UUID2: ");
  Serial.println(SERVICE_UUID2);
}

void loop() {
  // 코드를 추가하거나 루프를 비워둘 수 있습니다.
}
