#include <HardwareSerial.h>

HardwareSerial HM10(2); // RX=16, TX=17

void setup() {
  Serial.begin(9600);  // PC와 통신을 위한 시리얼 포트 초기화
  HM10.begin(9600, SERIAL_8N1, 16, 17);  // HM-10 모듈을 위한 시리얼 포트 초기화
  Serial.println("HM-10 Bluetooth device scanning...");
}

void loop() {
  // HM-10 모듈로부터 데이터 읽기
  if (HM10.available()) {
    String line = HM10.readStringUntil('\n');
    Serial.println(line);
  }

  if (Serial.available()) { // 시리얼 모니터로부터 데이터가 들어오는지 확인
    String input = Serial.readStringUntil('\n'); // 시리얼 모니터로부터 데이터 읽기
    HM10.println(input); // 읽은 데이터를 HM10으로 전송

    // 디버깅을 위해 전송한 데이터를 시리얼 모니터에 출력
    Serial.print("Sent to HM10: ");
    Serial.println(input);
  }
}

// AT
//
// AT+ROLE1
// AT+IMME1
// AT+SHOW1
// AT+DISC?
// AT+DISI?




// 연결 확인
// AT
// 모듈 주소AT+BAUD?
// AT+ADDR?
// 모듈 이름 확인
// AT+NAME?
// 배터리 체크
// AT+BATT?

// Baud rate 설정 
// AT+BAUD0
  // P1: Baud rate No.
  // 0---------9600
  // 1---------19200
  // 2---------38400
  // 3---------57600
  // 4---------115200
  // 5---------4800
  // 6---------2400
  // 7---------1200
  // 8---------230400
  // Default: 0(9600)

  // AT+ROLE1
    // 0 슬레이브
    // 1 마스터장치

// AT+IMME1
  // 1: 모듈에 전원이 켜져 있을 때, AT명령에만 응답하고 아무것도 하지 마십시오.
  // AT+START, AT+CON, AT+CONNL 명령이 수신됩니다.
  // 0: 전원이 켜지면 모듈이 시작됩니다.

// AT+SHOW1 이름 표시
// 0:Don’t show name
// 1:Show name Default


// AT+POWE3 전력 설정
  // 0: -23dbm
  // 1: -6dbm
  // 2: 0dbm
  // 3: 6dbm
  // Default: 2 

// AT+NAME? 이름 확인