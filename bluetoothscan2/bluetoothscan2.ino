#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <WiFi.h>
#include <WebServer.h>


// 접속할 WIFI Name /  WIFI Password
const char* ssid = "NNX-2.4G";
const char* password = "$@43skshslrtm";

// 고정 IP 설정
IPAddress ip(192, 168, 0, 88);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// 포트 설정
const int serverPort = 80;
WebServer server(serverPort);
int scanTime = 1; // 스캔 시간을 5초로 설정합니다.


// 와이파이 접속
void setup_wifi(){
    // 시리얼 통신 초기화(실행), 전송속도 설정

    // 고정 IP 설정
    if (!WiFi.config(ip, gateway, subnet)){
        Serial.println("STA Failed to configure");
    }
    // 먼저 WiFi 네트워크에 연결합니다.
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    // 와이파이가 접속이 됬는지 확인
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print("연결 시도중!");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Port address: ");
    Serial.println(serverPort);
}
void reconnectWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.disconnect();
        WiFi.config(ip, gateway, subnet);
        WiFi.begin(ssid, password);
        Serial.print("Reconnecting to WiFi");

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi reconnected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("Port address: ");
        Serial.println(serverPort);
    }
}
void callCancle() {
  if(!digitalRead(19)){
    digitalWrite(19, HIGH);
    delay(1000);
    digitalWrite(19, LOW);
    Serial.println("통화 종료");
    server.send(200, "text/plain", "통화 종료");
  }else{
    digitalWrite(19, LOW);
    delay(1000);
    digitalWrite(19, HIGH);
    Serial.println("통화 종료");
    server.send(200, "text/plain", "통화 종료");
  }
}

// 콜백 클래스를 정의합니다. 이 클래스는 스캔 중 발견된 각 장치에 대해 호출됩니다.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("장치 발견 ");
    // Serial.println(advertisedDevice.toString().c_str());
      Serial.print("Name: ");
      Serial.println(advertisedDevice.getName().c_str());

      // 장치 주소 출력
      // Serial.print("Address: ");
      // Serial.println(advertisedDevice.getAddress().toString().c_str());

      // 제조사 데이터 출력
      // Serial.print("Manufacturer Data: ");
      // Serial.println(advertisedDevice.getManufacturerData().c_str());

      // 서비스 UUID 출력
      Serial.println("UUID 목록:");
      for (int i = 0; i < advertisedDevice.getServiceUUIDCount(); i++) {
        Serial.println(advertisedDevice.getServiceUUID(i).toString().c_str());
      }

      // RSSI 출력
      // Serial.print("RSSI: ");
      // Serial.println(advertisedDevice.getRSSI());
  }
};

void setup() {
  Serial.begin(115200);
  // 핀모드
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  setup_wifi();
  server.on("/callcancle", callCancle);
  server.begin();


  // 블루투스 장치 스캔
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan(); // BLE 스캐너 생성
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); // 활성 스캔 모드를 사용합니다.
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // 더 적극적인 스캔을 위해 설정
}

void loop() {
  // 와이파이 연결 체크
  reconnectWiFi();
  // 5초 동안 스캔을 수행합니다.
  BLEScanResults foundDevices = BLEDevice::getScan()->start(scanTime, false);
  Serial.print("발견된 장치 수: ");
  Serial.println(foundDevices.getCount());
  Serial.println("스캔 종료");
  Serial.println("=============================");


  // 스캔을 멈추고, 잠시 후 다시 시작합니다.
  BLEDevice::getScan()->clearResults();
  server.handleClient();
  delay(1000);
  server.handleClient();
}
