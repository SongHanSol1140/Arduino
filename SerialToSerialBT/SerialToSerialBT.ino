#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// BLE 서비스 및 특성 UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// WIFI SSID & Password
const char *ssid = "NNX2-2.4G";
const char *password = "$@43skshslrtm";

void setup_wifi() {
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("연결 시도중!");
    }

    Serial.println("WiFi Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnectWiFi() {
  // 연결이 끊어지면 재연결을 시도
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi 연결 시도...");
    // WiFi 연결을 시도합니다.
    WiFi.begin(ssid, password);
    delay(3000);
    Serial.println("WiFi Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("연결 완료");
    }

    void onDisconnect(BLEServer* pServer) {
      Serial.println("연결 해제");
      pServer->startAdvertising(); // 연결 해제 후 다시 광고 시작
    }
};

void setup() {
  Serial.begin(115200);
  // setup_wifi();

  BLEDevice::init("ESP32-BLE"); // BLE 장치 이름 설정
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks()); // 콜백 설정
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                        CHARACTERISTIC_UUID,
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE |
                                        BLECharacteristic::PROPERTY_NOTIFY
                                      );

  pCharacteristic->addDescriptor(new BLE2902()); // Notifications을 위한 Descriptor 추가
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setMinInterval(100);
  pAdvertising->setMaxInterval(100);
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("BLE 서비스 및 광고 시작");
}

void loop() {
  
  
  // Wi-Fi 재연결 시도
  // reconnectWiFi();
  

  delay(1000); // 루프 지연

}
