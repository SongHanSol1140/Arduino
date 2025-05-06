// https://wiki.seeedstudio.com/grove_gesture_paj7660/
// 뒷면의 스위치 2번을 아래로 off
#include <Wire.h>
#include <pag7660.h>
#include "Gesture.h"

pag7660 GestureSensor; // Combined mode is used by default

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }
    Serial.println("\nPAG7660 TEST DEMO: Gesture combined mode.");

    Wire.begin(21, 22); // ESP32-WROOM의 SDA = GPIO 21, SCL = GPIO 22

    if (GestureSensor.init()) {
        Serial.println("PAG7660 initialization success");
    } else {
        Serial.println("PAG7660 initialization failed");
    }
    Serial.println("Please input your gestures:\n");
}

void loop() {
    pag7660_gesture_t result;
    if (GestureSensor.getResult(result)) {
        printResultCombinedMode(result);
    }
    delay(100);
}

void printResultCombinedMode(const pag7660_gesture_t &result) {
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
