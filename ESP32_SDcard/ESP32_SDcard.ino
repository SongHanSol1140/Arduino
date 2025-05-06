#include <SPI.h>
#include <SD.h>
#define SD_SCK     21
#define SD_MISO    22
#define SD_MOSI    23
#define SD_CS      5  // CS 핀은 원하는 GPIO로 설정
SPIClass customSPI(VSPI);  // VSPI 또는 HSPI 중 선택

bool initSDCard() {
    customSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    if (!SD.begin(SD_CS, customSPI)) {
        Serial.println("SD 카드 초기화 실패");
        return false;
    }
    Serial.println("SD 카드 초기화 성공");
    return true;
}
void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  while (!Serial);       // 시리얼 준비 대기

  Serial.println("SD 카드 초기화 중...");

  // SD 카드 초기화
  initSDCard();

  // 파일 존재 여부 확인
  if (SD.exists("/Hello.wav")) {
    Serial.println("파일 'Hello.wav'이(가) SD 카드에 존재합니다.");
  } else {
    Serial.println("파일 'Hello.wav'이(가) SD 카드에 없습니다.");
  }
}

void loop() {
  // 빈 루프
}
