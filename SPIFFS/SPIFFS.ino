// ESP32 SPIFFS공간에 업로드된 파일들 파일코드들 확인
#include "SPIFFS.h"
void setup() {
    Serial.begin(115200);  // 시리얼 포트 초기화
    delay(3000);
    // Mount SPIFFS
    if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
    }

    // List all files
    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file) {
    Serial.print("File: ");
    Serial.println(file.name()); // Print file name
    file = root.openNextFile();
    }
}

void loop() {
  
}
