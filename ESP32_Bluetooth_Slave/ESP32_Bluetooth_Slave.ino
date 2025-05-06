// ESP32_Bluetooth_Slave.ino
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// 캐릭터리스틱을 위한 콜백 클래스 (명령 수신 처리)
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    // std::string 대신 Arduino의 String 사용
    String rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      Serial.print("수신된 값: ");
      Serial.println(rxValue);

      // 예시: "ON" 명령 처리
      if (rxValue.equals("ON")) {
        Serial.println("해당 모듈 ON 처리");
        // 실제 ON 동작(LED 켜기 등)을 구현하세요.
      } else {
        Serial.println("알 수 없는 명령 수신");
      }
    }
  }
};

void setup() {
  Serial.begin(115200);

  // 모듈명은 각 모듈 구분에 따라 "Module2" 또는 "Module3" 등으로 설정
  BLEDevice::init("Module2");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  
  // 광고 패킷에 서비스 UUID를 포함시키도록 설정
  pAdvertising->addServiceUUID(SERVICE_UUID);
  
  pAdvertising->start();
  Serial.println("BLE Peripheral (하위 모듈) 시작!");
  // 자신의 블루투스 주소(MAC Address) 가져오기
  BLEAddress myAddress = BLEDevice::getAddress();

  // 시리얼 모니터에 주소 출력
  Serial.print("내 블루투스 주소: ");
  Serial.println(myAddress.toString().c_str());  // BLEAddress 객체를 문자열로 변환하여 출력
}

void loop() {
  // 주기적 작업이 있다면 추가 가능, 기본적으로 광고 후 명령 대기 상태
  delay(1000);
}
