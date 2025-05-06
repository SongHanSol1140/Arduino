// .ino
#include "wifi_mqtt.h"
#include "variables.h"
#include "door.h"
#include "sdCardModule.h"  // SD 카드 모듈 추가
#include "max98357.h"      // max98357 앰프 I2C 연결
// #include "lguTCP.h"


void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  // 현재 버튼으로 구현되어있으므로 추후에 센서로 변경시 _PULLUP삭제해서 INPUT으로 변경
  //
  pinMode(ENTRY_SENSOR_PIN, INPUT_PULLUP);      // 입장 SENSOR_PIN을 설정
  pinMode(EXIT_SENSOR_PIN, INPUT_PULLUP);       // 퇴장 SENSOR_PIN을 설정
  pinMode(Emergency_BUTTON_PIN, INPUT_PULLUP);  // 비상 호출 버튼

  pinMode(DOOR_PIN, OUTPUT);    // DOOR_PIN을 출력으로 설정
  digitalWrite(DOOR_PIN, LOW);  // 초기 상태 문 닫힘


  delay(100);
  // I2S 초기화
  initI2S(24000, 16, 1);

  // SD카드 초기화 확인 // SD카드에 .wav파일 저장해서 재생을 위해
  if (initSDCard()) {
    Serial.println("SD카드 초기화 완료");
  } else {
    Serial.println("SD카드 초기화 실패");
  }

  delay(100);
  // playWavNonBlocking("Hello.wav");  // max98357

  

  // WiFi 및 MQTT 설정
  setWifi();
  setMqtt();

  // TCP 서버 초기화
  // initTCPServer();


  setOpenTime();
  Serial.println("출입문 시스템 Setup");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!mqttClient.connected()) {
    setMqtt();
  }
  mqttClient.loop();

  // TCP 클라이언트 처리
  // handleTCPClients();

  // 문 및 센서 상태 체크
  checkSensors();
  // 비상용 버튼 눌림체크
  checkEmergencyButton();
  delay(100);
}
