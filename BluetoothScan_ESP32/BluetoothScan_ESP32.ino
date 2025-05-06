#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 2; // 스캔 시간을 5초로 설정합니다.

// 콜백 클래스를 정의합니다. 이 클래스는 스캔 중 발견된 각 장치에 대해 호출됩니다.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    // Serial.println(advertisedDevice.toString().c_str());
      Serial.write("Name:");
      Serial.write(advertisedDevice.getName().c_str()) + "\n";
      Serial.write("\n");
      // 장치 주소 출력
      Serial.write("Address:");
      Serial.write(advertisedDevice.getAddress().toString().c_str());
      Serial.write("\n");
      // 제조사 데이터 출력
      // Serial.print("Manufacturer Data: ");
      // Serial.println(advertisedDevice.getManufacturerData().c_str());

      // 서비스 UUID 출력
      Serial.write("UUID:");
      for (int i = 0; i < advertisedDevice.getServiceUUIDCount(); i++) {
        Serial.write(advertisedDevice.getServiceUUID(i).toString().c_str());
        Serial.write("\n");
      }
      
      // RSSI 출력
      // Serial.print("RSSI: ");
      // Serial.println(advertisedDevice.getRSSI());
    Serial.write("======");
    Serial.write("\n");
  }
};

void setup() {
  Serial.begin(115200);
  // 블루투스 장치 스캔
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan(); // BLE 스캐너 생성
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); // 활성 스캔 모드를 사용합니다.
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // 더 적극적인 스캔을 위해 설정
}

void loop() {
  // 5초 동안 스캔을 수행합니다.
  BLEScanResults foundDevices = BLEDevice::getScan()->start(scanTime, false);
  // Serial.write("Scan Device: ");
  // Serial.write(foundDevices.getCount());
  // Serial.write("\n");
  // Serial.write("Close Scan");

  // 스캔을 멈추고, 잠시 후 다시 시작합니다.
  BLEDevice::getScan()->clearResults();
  delay(1000);
}
