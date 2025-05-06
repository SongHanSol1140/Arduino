// 16번 핀 - 빨간색
// HIGH - 전화 받지 않음 - 수화기 내림
// LOW - 전화 받음 - 수화기 올림
// 아무런 핀설정을 하지않은 핀 17번에 파란선 연결
// 라즈베리파이에서 TCP서버로 발신인 번호를 받는순간 해당 ESP32로 callcancel 요청을 보냄

#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi 클라이언트 및 웹 서버 객체 선언
WiFiClient espClient;
WebServer server(80);

// SSID & Password
const char* ssid = "NNX-2.4G";
const char* password = "$@43skshslrtm";

int webPort = 80;

// 고정 IP 설정
IPAddress ip(192, 168, 0, 232); // 고정하고 싶은 IP(사용 중인 IP는 안됨)
IPAddress gateway(192, 168, 0, 1);  // 게이트웨이 IP
IPAddress subnet(255, 255, 255, 0); // 서브넷 마스크

void setup_wifi() {
    // Wi-Fi 설정
    if (!WiFi.config(ip, gateway, subnet)){
        Serial.println("STA Failed to configure");
    }

    // Wi-Fi에 연결
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    // Wi-Fi 연결 대기
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("연결 시도중!");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("PORT address: ");
    Serial.println(webPort);
}

// 루트 핸들러
void handle_root() {
    server.send(200, "text/html", "Hello from ESP8266!");
}

// 콜 취소 핸들러
void handle_call_cancel() {
  // delay 동안 LOW(전화받음(수화기올림))상태
    digitalWrite(16, LOW);   
    delay(500);               // 0.5초 동안 대기
    digitalWrite(16, HIGH);    
    server.send(200, "text/plain", "Call cancelled successfully");
    Serial.println("test");
}

void setup() {
    // 시리얼 통신 초기화
    Serial.begin(115200);
    // 핀 모드 설정
    pinMode(16, OUTPUT);

    // 핀 초기 상태를 LOW로 설정
    digitalWrite(16, HIGH);
    
    // Wi-Fi 설정 초기화
    setup_wifi();
    // 루트 URL에 대한 요청 처리 함수 설정
    server.on("/", handle_root);
    // /callcancel 경로에 대한 요청 처리 함수 설정
    server.on("/callcancel", handle_call_cancel);
    // 서버 시작
    server.begin();
}





void loop() {
    // Wi-Fi 연결 상태 확인
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WIFI 연결 끊김, 재연결 시도");
      setup_wifi();
    }

    // 클라이언트 요청 처리
    server.handleClient();
}
