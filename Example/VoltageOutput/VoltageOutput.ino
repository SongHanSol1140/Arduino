#include <WiFi.h>

const char ssid[] = "NNX2-2.4G";
const char password[] = "$@43skshslrtm";


void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // // 고정 IP 설정 - 미사용시 주석처리
    // const IPAddress local_IP(192, 168, 0, 5);  // 고정 IP 주소
    // const IPAddress gateway(192, 168, 0, 1);   // 게이트웨이 주소
    // const IPAddress subnet(255, 255, 255, 0);  // 서브넷 마스크
    // if (!WiFi.config(local_IP, gateway, subnet)) {
    //   Serial.println("STA Failed to configure");
    // }  // 고정IP 설정 끝
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
  // PWM 주파수와 해상도 설정
  const int freq = 5000;
  const int resolution = 12; // 8비트 0~255 12비트 0~4095

  // 각 핀을 PWM 모드로 설정하고 채널에 연결
  ledcAttach(32, freq, resolution);
  ledcAttach(33, freq, resolution);
  ledcAttach(25, freq, resolution);
  ledcAttach(26, freq, resolution);
  ledcAttach(27, freq, resolution);
  ledcAttach(13, freq, resolution);
  ledcAttach(14, freq, resolution);
  ledcAttach(4, freq, resolution);
  ledcAttach(2, freq, resolution);

  Serial.println("PWM 설정 완료");
}

void loop() {

  // 각 핀에 PWM 값 출력
  ledcWrite(32, 2000);
  ledcWrite(33, 1000);
  ledcWrite(25, 3000);
  ledcWrite(26, 4000);
  ledcWrite(27, 2048);
  ledcWrite(13, 50);
  ledcWrite(14, 50);
  ledcWrite(4, 50);
  ledcWrite(2, 50);
}
