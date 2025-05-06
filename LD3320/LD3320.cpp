// LD3320.cpp

#include "ld3320.h"
#include <SPI.h>

uint8_t g_Mic;
uint8_t MIC_VOL = 0x55;           // ADC 증폭 초기값
uint8_t speech_endpoint = 0x10;   // 음성 종단점 감지 초기값
uint8_t speech_start_time = 0x08; // 음성 시작 시간 초기값
uint8_t speech_end_time = 0x10;   // 음성 끝나는 시간 초기값
uint8_t voice_max_length = 0xC3;  // 최장 음성 길이, 기본값 20초
uint8_t noise_time = 0x02;        // 전원 투입 시 잡음 무시 시간
// uint8_t ASR_time 최대 시간
int readflag = 0;
int readnum = 0;

byte transfer(byte _data);

VoiceRecognition::VoiceRecognition() {}

int VoiceRecognition::read() // 인식 결과 읽기
{
    if (readflag == 1)
    {
        readflag = 0;
        return readnum;
    }
    return -1;
}
void update() // 인터럽트 서비스 함수
{
    uint8_t Asr_Count = 0;
    Serial.println("인터럽트 진입...");
    if ((readReg(0x2b) & 0x10) && readReg(0xb2) == 0x21 && readReg(0xbf) == 0x35) // 음성 인식 인터럽트 발생, DSP 유휴 상태, ASR 정상 종료 여부 확인
    {
        writeReg(0x29, 0);                  /////////// 인터럽트 종료
        writeReg(0x02, 0);                  ///////////// FIFO 인터럽트 종료
        Asr_Count = readReg(0xba);          // 인터럽트 보조 정보 읽기
        if (Asr_Count > 0 && Asr_Count < 4) ////// 인식 결과가 있는 경우
        {
            readnum = readReg(0xc5);
            readflag = 1;
        }
        writeReg(0x2b, 0);
        writeReg(0x1C, 0);
    }
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
    writeReg(0x1c, 0x09); //////// 마이크 설정 유지
    writeReg(0xbd, 0x20); ///////// 설정 유지
    writeReg(0x08, 0x01); /////////// → FIFO_DATA 초기화
    delay(1);
    writeReg(0x08, 0x00); //////////// 지정된 FIFO 초기화 후 00H 한 번 더 쓰기
    delay(1);
    writeReg(0xb2, 0xff); //////// 0xB2에 FF 쓰기
    writeReg(0x37, 0x06); //////// 인식 시작
    delay(5);
    writeReg(0x1c, g_Mic); //////// 마이크 선택
    writeReg(0x29, 0x10);  //////// 동기화 인터럽트 켜기
    writeReg(0xbd, 0x00);  ///////// 음성 인식 시작
}
void cSHigh()
{ // CS 핀 높임
    digitalWrite(CS, HIGH);
}
void cSLow()
{ // CS 핀 낮춤
    digitalWrite(CS, LOW);
}

void writeReg(unsigned char address, unsigned char value) //////// 레지스터 쓰기, 인자(레지스터 주소, 데이터)
{
    cSLow(); //// CS 핀 낮춤
    delay(10);
    transfer(0x04); //////////// 쓰기 명령
    transfer(address);
    transfer(value);
    cSHigh(); //// CS 핀 높임
}

unsigned char readReg(unsigned char address) /// 레지스터 읽기, 인자(레지스터 주소)
{
    unsigned char result;
    cSLow(); //// CS 핀 낮춤
    delay(10);
    transfer(0x05); /////////// 읽기 명령
    transfer(address);
    result = transfer(0x00);
    cSHigh(); /// CS 핀 높임
    return (result);
}

byte transfer(byte _data) ///////////////// SPI 전송 바이트
{
    int32_t i = 0;
    uint8_t data = 0;
    cSLow(); //// CS 핀 낮춤
    for (i = 7; i >= 0; i--)
    {
        // MSB 전송
        if (_data & (1 << i))
        {
            digitalWrite(SPI_MOSI_PIN, HIGH); // 비트가 1이면 HIGH로 설정
        }
        else
        {
            digitalWrite(SPI_MOSI_PIN, LOW); // 비트가 0이면 LOW로 설정
        }
        if (digitalRead(SPI_MISO_PIN))
        { // 전송 후 바로 수신
            data |= (1 << i);
        }
        /* 반드시 데이터 시트와 타이밍 다이어그램을 참조, 하강 에지 유효 */
        /* SPI 모드 3, 대기 시 CS=1, 첫 번째 변화 에지에서 트리거 */
        digitalWrite(SPI_SCK_PIN, LOW);
        delay(1);
        digitalWrite(SPI_SCK_PIN, HIGH);
        delay(1);
    }
    return data; // 수신 여부는 필요에 따라 결정
}

void VoiceRecognition::init(uint8_t mic) //////// 모듈 활성화, 매개변수는 마이크 선택 (MIC/MONO)이며 실크와 일치, SETUP에서 호출됨
{
    if (mic == MIC)
    {
        g_Mic = MIC;
    }
    else if (mic == MONO)
    {
        g_Mic = MONO;
    }
    pinMode(RSTB, OUTPUT);
    pinMode(CS, OUTPUT);
    cSHigh();

    pinMode(IRQ_PIN, INPUT_PULLUP);
    pinMode(SPI_MISO_PIN, INPUT);
    pinMode(SPI_MOSI_PIN, OUTPUT);
    pinMode(SPI_SCK_PIN, OUTPUT);

    //  #ifndef SOFTWARE_SPI
    //   // SS는 칩 선택이 아니더라도 출력 모드여야 함
    //   pinMode(LD_CHIP_SELECT_PIN, OUTPUT);
    //   digitalWrite(LD_CHIP_SELECT_PIN, HIGH); // 모든 SPI 장치 비활성화 (SS 핀 HIGH로 설정)
    //   // SPI 활성화, 마스터 모드, 클럭 비율 f_osc/128
    //   //SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);///// SPI 레지스터 초기화
    //   // 더블 속도 해제
    //   //SPSR &= ~(1 << SPI2X);// 2배 속도 해제
    // #endif  // SOFTWARE_SPI

    // SPCR = (SPCR & ~SPI_MODE_MASK) | 0x08; // SCK 기본 상태와 샘플링 시간 설정, 0x08은 SCK가 기본적으로 HIGH 상태, 하강 에지 유효
    reset(); // LD3320 리셋 작업

    // #if defined(__AVR_ATmega32U4__)
    //     attachInterrupt(1, update, LOW); // 인터럽트 활성화
    // #else
    //     attachInterrupt(0, update, LOW); // 인터럽트 활성화
    // #endif
    attachInterrupt(IRQ_PIN, update, FALLING); // 인터럽트 활성화

    ASR_init(); /// 음성 인식 초기화 함수
}

void VoiceRecognition::reset() // LD3320 리셋 작업
{
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
void VoiceRecognition::ASR_init() //////////// 음성 인식 모드 초기화
{
    // 상태 플래그 추가
    readReg(0x06);
    //      writeReg(0x17, 0x35);
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
    //      writeReg(0xb9, 0x00);
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

void VoiceRecognition::addCommand(char *pass, int num)
{
    int i;
    writeReg(0xc1, num);  // 문자 번호
    writeReg(0xc3, 0);    // 추가 시 00 입력
    writeReg(0x08, 0x04); // 초기화하지 않음
    delay(1);
    writeReg(0x08, 0x00);
    delay(1);
    for (i = 0; i <= 80; i++)
    {
        if (pass[i] == 0)
            break;
        writeReg(0x5, pass[i]); /// FIFO_EXT에 쓰기
    }
    writeReg(0xb9, i);    // 현재 추가된 문자열 길이 기록
    writeReg(0xb2, 0xff); ////////// 0xB2 전체에 FF 쓰기
    writeReg(0x37, 0x04); // 명령 추가
}

unsigned char VoiceRecognition::start() ////// 음성 인식 시작
{
    writeReg(0x35, MIC_VOL); //// ADC 증폭; 인식 범위 및 잡음에 영향
    writeReg(0xb3, speech_endpoint); // 음성 종단점 감지 설정
    writeReg(0xb4, speech_start_time); // 음성 시작 시간
    writeReg(0xb5, speech_end_time); // 음성 끝나는 시간
    writeReg(0xb6, voice_max_length); // 음성 최대 길이
    writeReg(0xb7, noise_time); // 잡음 시간
    writeReg(0x1c, 0x09); ////// 마이크 설정 유지
    writeReg(0xbd, 0x20); ////// 설정 유지
    writeReg(0x08, 0x01); ////// FIFO_DATA 초기화
    delay(1);
    writeReg(0x08, 0x00); ////// 지정된 FIFO 초기화 후 00H 한 번 더 쓰기
    delay(1);
    if (check_b2() == 0) ////// 0xB2 레지스터 읽기 함수, DSP가 유휴 상태가 아니면 0 반환
    {
        return 0;
    }
    writeReg(0xb2, 0xff); ////// 0xB2에 FF 쓰기
    writeReg(0x37, 0x06); ////// 음성 인식 시작
    delay(5);
    writeReg(0x1c, g_Mic); ////// 마이크 선택
    writeReg(0x29, 0x10);  ////// 동기화 인터럽트 켜기
    writeReg(0xbd, 0x00);  ////// 음성 인식 시작
    return 1; //// 1 반환
}

int check_b2() ////// 칩이 정상 작동 중인지, 또는 DSP가 유휴 상태인지 확인, 유휴/정상이면 1 반환
{
    for (int j = 0; j < 10; j++)
    {
        if (readReg(0xb2) == 0x21)
        {
            return 1;
        }
        delay(10);
    }
    return 0;
}

void VoiceRecognition::micVol(uint8_t vol) // ADC 증폭 조정, 매개변수 (0x00 ~ 0xFF, 권장값 10-60)
{
    MIC_VOL = vol;
    writeReg(0x35, MIC_VOL); //// ADC 증폭; 인식 범위 및 잡음에 영향
}

void VoiceRecognition::speechEndpoint(uint8_t speech_endpoint_) // 음성 종단점 감지 조정, 매개변수 (0x00 ~ 0xFF, 권장값 10-40)
{
    speech_endpoint = speech_endpoint_;
    writeReg(0xb3, speech_endpoint); // 음성 종단점 감지 설정
}

void VoiceRecognition::speechStartTime(uint8_t speech_start_time_) // 음성 시작 시간 조정, 매개변수 (0x00 ~ 0x30, 단위 10ms)
{
    speech_start_time = speech_start_time_;
    writeReg(0xb4, speech_start_time); // 음성 시작 시간 설정
}

void VoiceRecognition::speechEndTime(uint8_t speech_end_time_) // 음성 끝나는 시간(말의 끝 시간) 조정, 매개변수 (0x00 ~ 0xC3, 단위 10ms)
{
    speech_end_time = speech_end_time_;
    writeReg(0xb5, speech_end_time); // 음성 끝나는 시간 설정
}

void VoiceRecognition::voiceMaxLength(uint8_t voice_max_length_) // 최대 음성 길이 조정, 매개변수 (0x00 ~ 0xC3, 단위 100ms)
{
    voice_max_length = voice_max_length_;
    writeReg(0xb6, voice_max_length); // 음성 최대 길이 설정
}

void VoiceRecognition::noiseTime(uint8_t noise_time_) // 전원 투입 시 잡음 무시 시간 설정, 매개변수 (0x00 ~ 0xff, 단위 20ms)
{
    noise_time = noise_time_;
    writeReg(0xb7, noise_time); // 잡음 시간 설정
}
