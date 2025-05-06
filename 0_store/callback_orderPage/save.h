// // .ino
// #include <WiFiClientSecure.h>
// #include <HTTPClient.h>

// #include "variables.h"
// #include "SHA512.h"
// #include "wifi_mqtt.h"
// #include "lguTCP.h"


// void setup() {
//   Serial.begin(115200);
//   delay(100);

//   // ① Centrex 비밀번호 SHA-512 해시로 변환
//   String centrex_password = sha512(centrex_raw_password);
//   Serial.println("Centrex SHA-512 password:");
//   Serial.println(centrex_password);

//   // WiFi 및 MQTT 설정
//   setWifi();

//   // TCP 서버 초기화
//   initTCPServer();
//   Serial.println("출입문 시스템 Setup");
// }

// void loop() {
//   if (WiFi.status() != WL_CONNECTED) {
//     setWifi();
//   }
//   // TCP 클라이언트 처리
//   handleTCPClients();
//   delay(10);

//   if (!phoneNumber.isEmpty()) {
//     Serial.println("발신 테스트");
//     sendSMS("01031277711", "Hello World!");
//     phoneNumber = "";
//   }
// }



// void sendSMS(const char *destNumber, const char *message) {
//   // Wi-Fi 연결 확인
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi not connected");
//     return;
//   }

//   // SHA-512 해시 생성
//   String centrex_password = sha512(centrex_raw_password);

//   // 요청 URL 구성
//   String url = String("https://centrex.uplus.co.kr/RestApi/smssend?")
//                + "id=" + urlEncode(centrex_id)
//                + "&pass=" + urlEncode(centrex_password)
//                + "&destnumber=" + urlEncode(destNumber)
//                + "&smsmsg=" + urlEncode(message);
//   Serial.println("Request URL (from wifi_mqtt.cpp): " + url);
//   // HTTPS 클라이언트 준비
//   WiFiClientSecure client;
//   client.setInsecure();  // 인증서 검증 생략 (프로덕션에선 CA 인증서 설정 권장)

//   HTTPClient https;
//   if (https.begin(client, url)) {
//     int httpCode = https.POST("");  // 본문 없이 POST 요청
//     if (httpCode > 0) {
//       String payload = https.getString();
//       Serial.printf("HTTP %d\nResponse: %s\n", httpCode, payload.c_str());
//     } else {
//       Serial.printf("POST failed, error: %s\n", https.errorToString(httpCode).c_str());
//     }
//     https.end();
//   } else {
//     Serial.println("Unable to connect");
//   }
// }
