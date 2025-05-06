// XIAO_ESP32C3 Board에 업로드
// https://wiki.seeedstudio.com/grove_gesture_paj7660/
// 업로드시 부팅버튼을 누르고 리셋누르면 업로드모드

// 아마 ESP32 + PAJ7660(제스처센서) + SZH-SM001(음성인식센서)를 같이사용하므로 XAIO_ESP32C3버전은 사용하지않을듯함
// README에 i2c버전 사진 참조해서사용
// D4(SDA), D5(SCL)
// README 폴더에 PAJ7660 배선 사진 확인
// 나머지핀은 사용안함
#include "Gesture.h"
#include "wifiSetup.h"
pag7660 Gesture; // Combined mode is used by default

void setup() {
    Serial.begin(115200);
    while(!Serial) {
        delay(100);
    }
    Serial.println("\nPAG7660 TEST DEMO: Gesture combined mode.");
    
    if(Gesture.init()) {
        Serial.println("PAG7660 initialization success");
    } else {
        Serial.println("PAG7660 initialization failed");
    }
    Serial.println("Please input your gestures:\n");

    setWifi();
}

void loop() {
  setWifi();
    pag7660_gesture_t result;
    if (Gesture.getResult(result)) {
        printResultCombinedMode(result);
    }
    delay(100);
}

void printResultCombinedMode(const pag7660_gesture_t& result) {
    const char *cursor_str[] = {
        NULL,
        "Tap",
        "Grab",
        "Pinch",
    };
    switch (result.type) {
    case 0:
        switch (result.cursor.type) {
        case 1:
        case 2:
        case 3:
            if (result.cursor.select)
                Serial.println(cursor_str[result.cursor.type]);
            break;
        default:
            break;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        Serial.print(result.type);
        Serial.println("-finger");
        break;
    case 6:
        Serial.print("Rotate Right ");
        Serial.println(result.rotate);
        break;
    case 7:
        Serial.print("Rotate Left ");
        Serial.println(result.rotate);
        break;
    case 8:
        Serial.println("Swipe Left");
        break;
    case 9:
        Serial.println("Swipe Right");
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        Serial.print(result.type - 19 + 1);
        Serial.println("-finger push");
        break;
    default:
        break;
    }
}