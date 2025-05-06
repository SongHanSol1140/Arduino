/*
  유의 사항
    업로드시 파티션을 NO OTA 2MB / 2MB로 해주세요
    Default설정은 블루투스와 와이파이/MQTT를 사용하기에 APP저장공간이 부족합니다.
*/
// ESP32_Bluetooth_Master.ino
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "wifi_mqtt.h"
#include "variables.h"

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

bool doConnect = false;
BLEAdvertisedDevice* targetDevice = nullptr;

// 스캔 결과를 처리하기 위한 콜백 클래스
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    // 광고 데이터에 원하는 서비스 UUID가 있는지 확인
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      Serial.println("제어 대상 기기 발견!");
      // Serial.println(advertisedDevice.toString().c_str());
      targetDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      BLEDevice::getScan()->stop();  // 원하는 기기를 찾으면 스캔 중지
    }
    Serial.print("발견된 기기: ");
    Serial.println(advertisedDevice.toString().c_str());
  }
};

BLEClient* pClient = nullptr;

bool connectAndSendCommand() {
  pClient = BLEDevice::createClient();
  Serial.println("BLE 클라이언트 생성됨");

  // 목표 기기에 연결
  pClient->connect(targetDevice);
  Serial.println("연결 성공!");

  // 지정 서비스 검색
  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    Serial.println("해당 서비스 없음!");
    pClient->disconnect();
    return false;
  }

  // 캐릭터리스틱 검색
  BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("해당 캐릭터리스틱 없음!");
    pClient->disconnect();
    return false;
  }

  // 명령 전송 ("ON")
  String command = "ON";  // Arduino String 사용
  pRemoteCharacteristic->writeValue(command);
  Serial.println("명령 전송 완료: ON");

  return true;
}

void setup() {
  Serial.begin(115200);
  delay(100);
  setWifi();
  setMqtt();
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!client.connected()) {
    setMqtt();
  }
  client.loop();

  // if (doConnect) {
  //   if (connectAndSendCommand()) {
  //     Serial.println("하위 모듈에 명령 전달 성공!");
  //   } else {
  //     Serial.println("명령 전달 실패");
  //   }
  // }
  if (connectAndSendCommand()) {
    Serial.println("하위 모듈에 명령 전달 성공!");
  } else {
    Serial.println("명령 전달 실패");
  }
  delay(1000);
}
