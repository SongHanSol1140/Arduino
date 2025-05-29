#include <Arduino.h>
#include <NimBLEDevice.h>

// --- UUID 정의 ---
// 허용문자 0-9, a-f
#define SERVICE_UUID           "12345678-1234-1234-1234-abcdef000000"
#define CHARACTERISTIC_UUID_RX "12345678-1234-1234-1234-0123456789aa"
#define CHARACTERISTIC_UUID_TX "12345678-1234-1234-1234-0123456789bb"

// 전역 핸들러
NimBLEAdvertising*    pAdvertising;
NimBLECharacteristic* pTxCharacteristic;

// ─── RX 쓰기 콜백 ─────────────────────────────────────────
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

// ─── 서버 콜백 ───────────────────────────────────────────
class MyServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo) override {
    Serial.println("▶ Client connected");
  }
  void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason) override {
    Serial.println("◀ Client disconnected, restarting advertising");
    pAdvertising->start();
  }
};

void setup() {
  Serial.begin(115200);
  delay(100);

  // 1) NimBLE 초기화: 이름을 "peripheral_esp32_1"로 지정
  NimBLEDevice::init("peripheral_esp32_1");  
  // (옵션) 보안 파라미터 설정
  NimBLEDevice::setSecurityAuth(true, true, true);
  // ───> 최대 연결 수 변경은 nimconfig.h 에서 NIMBLE_MAX_CONNECTIONS 을 조정하세요.

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

  // 4) 광고 시작 (한 번만 호출)
  pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
  Serial.println("Advertising Started");
}

void loop() {
  // NimBLE 스택이 백그라운드에서 저전력 모드를 관리합니다.
  delay(1000);
}
