// https://wiki.dfrobot.com/Laser_Ranging_Sensor_RS485_4m_SKU_SEN0492
// 빨강선 : VCC
// 노란선 : A
// 초록선 : B
// 검은선 : GND

// VCC랑 그라운드를 전력에 같이연결
// RS485 to TTL 컨버터에 A => A / B => B연결
// 일반적인 TX / RX 와 다르게 RX - RX / TX - TX로 연결해야함
#include <HardwareSerial.h>

#define RXD2 16
#define TXD2 17

HardwareSerial RS485(2);

void setup() {
    Serial.begin(115200);
    RS485.begin(115200, SERIAL_8N1, RXD2, TXD2);
    
    Serial.println("Starting address scan...");
    scanAddresses();
}

void loop() {
    // 필요한 경우 여기에 추가 코드
}

void scanAddresses() {
    for (uint8_t addr = 1; addr <= 247; addr++) {
        if (checkAddress(addr)) {
            Serial.print("Device found at address: 0x");
            Serial.println(addr, HEX);
        }
    }
    Serial.println("Scan complete");
}

bool checkAddress(uint8_t addr) {
    uint8_t cmd[] = {addr, 0x03, 0x00, 0x34, 0x00, 0x01, 0x00, 0x00};
    uint16_t crc = calculateCRC(cmd, 6);
    cmd[6] = crc & 0xFF;
    cmd[7] = (crc >> 8) & 0xFF;
    
    RS485.write(cmd, sizeof(cmd));
    RS485.flush();
    
    delay(100);  // 응답 대기
    
    if (RS485.available()) {
        // 응답 데이터 읽기 (실제 사용 시 응답 검증 필요)
        while(RS485.available()) {
            RS485.read();
        }
        return true;
    }
    
    return false;
}

uint16_t calculateCRC(uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;
    for (uint8_t pos = 0; pos < length; pos++) {
        crc ^= (uint16_t)data[pos];
        for (uint8_t i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}