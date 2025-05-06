// main.ino
#include "esp_sleep.h"
#include "wifiSetup.h"
#include "mqttSetup.h"
#include "sound.h"

// 라이트 슬립모드 전환 시간
int WAKEUP_TIME = 10000;
// 버튼 누르는 시간
int GPIO32_TIMER = 3000;
int GPIO33_TIMER = 500;


// 로봇 호출(32) / 호출취소(33) /
#define callCleanBot (gpio_num_t)32
#define callCleanBotCancel (gpio_num_t)33


unsigned long cleaningRobotTimer = 0; // 마지막으로 상태를 변경한 시간을 저장
bool timerActive = false; // 타이머가 활성화되었는지 추적
bool justWokeUp = true; // 슬립 모드에서 깨어났음을 추적하는 변수
unsigned long wakeUpTime = 0;

//---------------------------------------------------------------
long pressDuration(int button, unsigned long duration){
    long startTime = millis();
    while (digitalRead(button) == LOW)
    { // duration뒤에 버튼 상태가 LOW라면
        if (millis() - startTime >= duration)
        {
            return 1;
        }
    }
    return 0;
}
//---------------------------------------------------------------
void setup(){
    Serial.begin(115200); // 시리얼 통신 초기화
    setWifi(); // WIFI 접속
    setMQTT(); // MQTT 접속
    // BUtton
    pinMode(callCleanBot, INPUT_PULLUP);
    pinMode(callCleanBotCancel, INPUT_PULLUP);

    // Initialize SPIFFS
    if (!SPIFFS.begin()){
        Serial.println("Failed to mount file system");
        return;
    }
    
    esp_sleep_enable_ext0_wakeup(callCleanBot, 0);
}

// ────────────────────────────────────────────────────────────────────────────────


void loop(){
    server.handleClient();
    client.loop();
    reconnectWifi();
    reconnectMQTT();
    if (justWokeUp) {
        wakeUpTime = millis(); // 깨어난 시간을 업데이트
        justWokeUp = false; // 초기화 코드를 한 번만 실행하도록 설정
    }
    // ────────────────────────────────────────────────────────────────────────────────
    // 호출
    if(!digitalRead(callCleanBot) && cleaningRobotState == false){
        // 3초간 버튼이 눌릴 때까지 대기
        long pressTime = pressDuration(callCleanBot, GPIO32_TIMER);
        if (pressTime == 0) {
            Serial.println("3초간 눌리지 않았습니다.");
            return;
        }
        playWav("callcleaningbot");
        Serial.println("호출 완료 청소봇을 불러옵니다.");
        sendMqttJson(true);
        
        cleaningRobotState = true; // 호출 상태
        cleaningRobotTimer = millis(); // 현재 시간 저장
        timerActive = true; // 타이머 시작

    }else if(!digitalRead(callCleanBot) && cleaningRobotState == true){
        Serial.print("이미 호출 중 입니다.");
    }

    // 호출 취소
    if(!digitalRead(callCleanBotCancel) && cleaningRobotState == true){
        long pressTime = pressDuration(callCleanBotCancel, GPIO33_TIMER);
        if (pressTime == 0) {
            Serial.println("0.5초간 눌리지 않았습니다.");
            return;
        }
        Serial.println("청소봇 호출을 취소합니다.");
        playWav("canclecallcleaningbot");
        sendMqttJson(false);
        cleaningRobotState = false; // 호출 상태
        timerActive = false; // 타이머 비활성화
        return;
    }

    // 타이머가 활성화되어 있고, 5분이 지났다면 cleaningRobotState를 false로 변경
    if (timerActive && millis() - cleaningRobotTimer >= 300000) { // 5분 = 300,000밀리초
        cleaningRobotState = false; // 상태를 false로 변경
        timerActive = false; // 타이머 비활성화
    }

    // n초 후 Light Sleep Mode
    if (millis() - wakeUpTime >= WAKEUP_TIME) {
        Serial.println("Light Sleep Mode");

        // WiFi 및 MQTT 연결 종료
        client.disconnect(); 
        WiFi.disconnect(true);
        delay(100);

        justWokeUp = true; // 다시 깨어났을 때 초기화 코드를 실행하도록 설정
        Serial.flush();
        esp_light_sleep_start(); // Light Sleep 모드 진입
    }
}

