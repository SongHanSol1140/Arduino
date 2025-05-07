#include "sdCardModule.h"
#include "variables.h"


SPIClass customSPI(VSPI);  // VSPI 또는 HSPI 중 선택

bool initSDCard() {
    customSPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN, customSPI, 4000000)) {  // SPI 클럭을 4MHz로 설정

        Serial.println("SD 카드 초기화 실패");
        return false;
    }
    Serial.println("SD 카드 초기화 성공");
    return true;
}

// SD카드에 파일이 존재하는지 체크하는 테스트용 함수
bool checkFileExists(const char* filename) {
    if (SD.exists(filename)) {
        Serial.print("파일 발견: ");
        Serial.println(filename);
        return true;
    } else {
        Serial.print("파일 없음: ");
        Serial.println(filename);
        return false;
    }
}
