// .ino
#include <WiFi.h>
#include "variables.h"
#include "webPage.h"
#include "pwmControl.h"
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
}

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 고정 IP 설정 - 미사용시 주석처리
    const IPAddress local_IP(192, 168, 0, 111);  // 고정 IP 주소
    const IPAddress gateway(192, 168, 0, 1);    // 게이트웨이 주소
    const IPAddress subnet(255, 255, 255, 0);   // 서브넷 마스크
    if (!WiFi.config(local_IP, gateway, subnet)) {
      Serial.println("STA Failed to configure");
    }  // 고정IP 설정 끝
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("connecting wifi...");
      delay(1000);
    }
    Serial.print("Wifi IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("WIFI connected!");
  }
};

void setup() {
  Serial.begin(115200);
  setWifi();

  // PWM 설정
  ledcAttach(pwmPin, pwmFreq, pwmResolution);

  // 버튼 설정
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);

  Serial.println("Press the button to start/stop PWM output");


  setupWebServer();
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    if (pwmRunning) {
      pwmRunning = false;
      Serial.println("Stopping PWM output");
      ledcWrite(pwmPin, 0);
      currentDuty = 0;
    } else {
      pwmRunning = true;
      Serial.println("Starting PWM output");
      softStart();
    }

    delay(50);  // 디바운싱
  }

  Serial.printf("Current duty: %.2f%%\n", currentDuty);
  delay(1000);
}