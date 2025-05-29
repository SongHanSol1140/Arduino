// XIAO.nRF52840_BLE.ino
// XIAO-nRF52840

/* 환경설정 - 기본설정 - 추가보드 관리자 URL
 *
 * https://files.seeedstudio.com/arduino/package_seeed_index.json
 * Seeed nRF52 mbed-enabled Boards 설치
 * Seeed XIAO nRF52840 Sense 설정
 *
 * 맥북에서 컴파일시 adafruit-nrfutil 이라는 문구가 에러에 보인다면
 * chmod +x ~/Library/Arduino15/packages/Seeeduino/hardware/nrf52/1.1.10/tools/adafruit-nrfutil/macos/adafruit-nrfutil
 *
 * 업로드후 에러라고 나오는데 코드는 정상작동함
 */
#include <Arduino.h>
#include <ArduinoBLE.h>
// --- UUID 정의 ---
// 허용문자 0-9, a-f
#define SERVICE_UUID "12345678-1234-1234-1234-abcdef000000"
#define CHARACTERISTIC_UUID_RX "12345678-1234-1234-1234-0123456789aa"
#define CHARACTERISTIC_UUID_TX "12345678-1234-1234-1234-0123456789bb"

char TABLE_NUMBER = '1';



BLEDevice peripheral;
BLECharacteristic rxChar;
BLECharacteristic txChar;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!BLE.begin()) {
    Serial.println("ArduinoBLE 초기화 실패!");
    while (1)
      ;
  }
  Serial.println("클라이언트 시작, 스캔 준비...");
}

void loop() {
  // 1) 스캔 시작 (5초 동안)
  BLE.scan();
  unsigned long scanStart = millis();
  Serial.println("스캔 중...");
  while (millis() - scanStart < 5000) {
    BLEDevice dev = BLE.available();
    if (dev) {
      // 디버깅용
      Serial.print("  [발견] ");  // 디버깅: 발견된 모든 장치 출력
      Serial.print(" | UUID: ");
      Serial.println(dev.advertisedServiceUuid());
      // UUID 확인
      if (dev.advertisedServiceUuid() == SERVICE_UUID) {
        peripheral = dev;
        Serial.println(">>> 타겟 서버 발견! <<<");
        break;  // 찾았으면 스캔 중지
      }
    }
  }

  BLE.stopScan();

  if (!peripheral) {
    Serial.println("서버를 찾지 못함, 재시도");
    delay(1000);
    return;
  }

  // 2) 연결
  Serial.print("발견: ");
  Serial.println(peripheral.localName());
  if (!peripheral.connect()) {
    Serial.println("연결 실패");
    delay(1000);
    return;
  }
  Serial.println("서버 연결됨");

  // 3) GATT 탐색
  if (!peripheral.discoverAttributes()) {
    Serial.println("특성 탐색 실패");
    peripheral.disconnect();
    return;
  }
  rxChar = peripheral.characteristic(CHARACTERISTIC_UUID_RX);
  txChar = peripheral.characteristic(CHARACTERISTIC_UUID_TX);

  // 4) notify 구독
  txChar.subscribe();
  // txChar.valueUpdated();
  // 5) 쓰기 & 응답 읽기
  rxChar.writeValue((const uint8_t*)&TABLE_NUMBER, 1);
  Serial.print("보냄: ");
  Serial.println(TABLE_NUMBER);

  unsigned long t0 = millis();
  while (millis() - t0 < 500) {
    BLE.poll();
    delay(100);
  }
  if (txChar.valueUpdated()) {
    uint8_t buf[16];
    int len = txChar.readValue(buf, sizeof(buf));
    Serial.print("응답: ");
    for (int i = 0; i < len; i++) Serial.print((char)buf[i]);
    Serial.println();
  }

  // 6) 연결 해제 후 슬립 모드 대체 지연
  // A
  peripheral.disconnect();
  Serial.println("연결 종료, 5초 슬립");
  delay(5000);
  // // B
  // if (txChar.valueUpdated()) {
  // peripheral.disconnect();
  // Serial.println("응답 받고 연결 종료");
  // delay(5000);
  // }
}