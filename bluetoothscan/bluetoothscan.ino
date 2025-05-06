#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // 스캔 시간을 5초로 설정합니다.

// 콜백 클래스를 정의합니다. 이 클래스는 스캔 중 발견된 각 장치에 대해 호출됩니다.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("장치 발견: ");
    Serial.println(advertisedDevice.toString().c_str());

    // 발견된 장치의 모든 서비스 UUID를 출력합니다.
    Serial.println("UUID 목록:");
    for (int i = 0; i < advertisedDevice.getServiceUUIDCount(); i++) {
      Serial.println(advertisedDevice.getServiceUUID(i).toString().c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("BLE 장치 스캔 시작");

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
  Serial.print("발견된 장치 수: ");
  Serial.println(foundDevices.getCount());
  Serial.println("스캔 종료");

  // 스캔을 멈추고, 잠시 후 다시 시작합니다.
  BLEDevice::getScan()->clearResults();
  delay(2000);
}
