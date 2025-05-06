#include "ld3320.h"

uint8_t g_Mic;
int RSTB = 5; // RSTB 핀 (ESP32의 사용 가능한 GPIO 핀)
int CS = 15;  // CS 핀 (ESP32의 사용 가능한 GPIO 핀)
int WR = 16; // WR 핀 (ESP32의 사용 가능한 GPIO 핀)
int interruptPin = 4; // 인터럽트 핀 (ESP32의 사용 가능한 GPIO 핀)

uint8_t MIC_VOL = 0x55; // ADC 게인 초기값
uint8_t speech_endpoint = 0x10; // 음성 종료점 초기값
uint8_t speech_start_time = 0x08; // 음성 시작 시간 초기값
uint8_t speech_end_time = 0x10; // 음성 종료 시간 초기값
uint8_t voice_max_length = 0xC3; // 최대 음성 길이, 기본값 20초
uint8_t noise_time = 0x02; // 소음 시간

volatile int readflag = 0;
volatile int readnum = 0;
VoiceRecognition* VoiceRecognitionInstance = nullptr; // 전역 인스턴스 포인터

VoiceRecognition::VoiceRecognition() {}

int VoiceRecognition::read() {
    if (readflag == 1) {
        readflag = 0;
        return readnum;
    }
    return -1;
}

void IRAM_ATTR VoiceRecognition::updateWrapper() {
    if (VoiceRecognitionInstance != nullptr) {
        VoiceRecognitionInstance->update();
    }
}

void VoiceRecognition::update() {
    uint8_t Asr_Count = 0;
    if ((readReg(0x2b) & 0x10) && readReg(0xb2) == 0x21 && readReg(0xbf) == 0x35) {
        writeReg(0x29, 0);
        writeReg(0x02, 0);
        Asr_Count = readReg(0xba);
        if (Asr_Count > 0 && Asr_Count < 4) {
            readnum = readReg(0xc5);
            readflag = 1;
        }
        writeReg(0x2b, 0);
        writeReg(0x1C, 0);
    }
}

void VoiceRecognition::cSHigh() {
    digitalWrite(CS, HIGH);
}

void VoiceRecognition::cSLow() {
    digitalWrite(CS, LOW);
}

void VoiceRecognition::writeReg(uint8_t address, uint8_t value) {
    cSLow();
    digitalWrite(WR, LOW); // WR 핀을 LOW로 설정
    delayMicroseconds(10);
    SPI.transfer(0x04);
    SPI.transfer(address);
    SPI.transfer(value);
    digitalWrite(WR, HIGH); // WR 핀을 HIGH로 설정
    cSHigh();
}

uint8_t VoiceRecognition::readReg(uint8_t address) {
    uint8_t result;
    cSLow();
    digitalWrite(WR, LOW); // WR 핀을 LOW로 설정
    delayMicroseconds(10);
    SPI.transfer(0x05);
    SPI.transfer(address);
    result = SPI.transfer(0x00);
    digitalWrite(WR, HIGH); // WR 핀을 HIGH로 설정
    cSHigh();
    return result;
}

void VoiceRecognition::init(uint8_t mic) {
    if (mic == MIC) {
        g_Mic = MIC;
    } else if (mic == MONO) {
        g_Mic = MONO;
    }

    pinMode(RSTB, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(WR, OUTPUT); // WR 핀을 출력으로 설정
    digitalWrite(WR, HIGH); // WR 핀을 HIGH로 설정 (필요에 따라 조정)

    cSHigh();

    // SPI.begin(sck, miso, mosi, ss);
    SPI.begin(18, 19, 23, CS); // SCK, MISO, MOSI, CS

    reset();

    pinMode(interruptPin, INPUT_PULLUP);

    // 전역 인스턴스 포인터 설정
    VoiceRecognitionInstance = this;

    attachInterrupt(digitalPinToInterrupt(interruptPin), VoiceRecognition::updateWrapper, FALLING);

    ASR_init();
}

void VoiceRecognition::reset() {
    digitalWrite(RSTB, HIGH);
    delay(1);
    digitalWrite(RSTB, LOW);
    delay(1);
    digitalWrite(RSTB, HIGH);
    delay(1);
    cSLow();
    delay(1);
    cSHigh();
    delay(1);
    writeReg(0xb9, 0x00);
}

void VoiceRecognition::ASR_init() {
    readReg(0x06);
    delay(10);
    readReg(0x06);
    writeReg(0x89, 0x03);
    delay(5);
    writeReg(0xcf, 0x43);
    delay(5);
    writeReg(0xcb, 0x02);
    writeReg(0x11, PLL_11);
    writeReg(0x1e, 0x00);
    writeReg(0x19, PLL_ASR_19);
    writeReg(0x1b, PLL_ASR_1B);
    writeReg(0x1d, PLL_ASR_1D);
    delay(10);
    writeReg(0xcd, 0x04);
    writeReg(0x17, 0x4c);
    delay(5);
    writeReg(0xcf, 0x4f);
    writeReg(0xbd, 0x00);
    writeReg(0x17, 0x48);
    delay(10);
    writeReg(0x3c, 0x80);
    writeReg(0x3e, 0x07);
    writeReg(0x38, 0xff);
    writeReg(0x3a, 0x07);
    writeReg(0x40, 0);
    writeReg(0x42, 8);
    writeReg(0x44, 0);
    writeReg(0x46, 8);
    delay(1);
}

void VoiceRecognition::addCommand(char *pass, int num) {
    int i;
    writeReg(0xc1, num);
    writeReg(0xc3, 0);
    writeReg(0x08, 0x04);

    delay(1);
    writeReg(0x08, 0x00);
    delay(1);
    for (i = 0; i <= 80; i++) {
        if (pass[i] == 0)
            break;
        writeReg(0x05, pass[i]);
    }
    writeReg(0xb9, i);
    writeReg(0xb2, 0xff);
    writeReg(0x37, 0x04);
}

unsigned char VoiceRecognition::start() {
    writeReg(0x35, MIC_VOL);

    writeReg(0xb3, speech_endpoint);

    writeReg(0xb4, speech_start_time);

    writeReg(0xb5, speech_end_time);

    writeReg(0xb6, voice_max_length);

    writeReg(0xb7, noise_time);

    writeReg(0x1c, 0x09);

    writeReg(0xbd, 0x20);
    writeReg(0x08, 0x01);
    delay(1);
    writeReg(0x08, 0x00);
    delay(1);
    if (check_b2() == 0) {
        return 0;
    }
    writeReg(0xb2, 0xff);

    writeReg(0x37, 0x06);
    delay(5);
    writeReg(0x1c, g_Mic);
    writeReg(0x29, 0x10);
    writeReg(0xbd, 0x00);

    return 1;
}

int VoiceRecognition::check_b2() {
    for (int j = 0; j < 10; j++) {
        if (readReg(0xb2) == 0x21) {
            return 1;
        }
        delay(10);
    }
    return 0;
}

void VoiceRecognition::micVol(uint8_t vol) {
    MIC_VOL = vol;
    writeReg(0x35, MIC_VOL);
}

void VoiceRecognition::speechEndpoint(uint8_t speech_endpoint_) {
    speech_endpoint = speech_endpoint_;
    writeReg(0xb3, speech_endpoint);
}

void VoiceRecognition::speechStartTime(uint8_t speech_start_time_) {
    speech_start_time = speech_start_time_;
    writeReg(0xb4, speech_start_time);
}

void VoiceRecognition::speechEndTime(uint8_t speech_end_time_) {
    speech_end_time = speech_end_time_;
    writeReg(0xb5, speech_end_time);
}

void VoiceRecognition::voiceMaxLength(uint8_t voice_max_length_) {
    voice_max_length = voice_max_length_;
    writeReg(0xb6, voice_max_length);
}

void VoiceRecognition::noiseTime(uint8_t noise_time_) {
    noise_time = noise_time_;
    writeReg(0xb7, noise_time);
}
