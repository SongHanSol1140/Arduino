// wifi_mqtt.cpp
#include "wifi_mqtt.h"
#include "variables.h"
#include "SHA512.h"

// sendsms
#include <WiFiClientSecure.h>  // HTTPS 통신
#include <HTTPClient.h>        // HTTP 요청


WiFiClient net;

void setWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    // 미사용시 주석처리
    // 고정 IP 설정
    if (!WiFi.config(wifiIP, gateway, subnet, dns)) {
      Serial.println("STA Failed to configure");
    }
    // 고정IP 설정 끝

    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("connecting wifi...");
      delay(1000);
    }
    Serial.print("Wifi IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("WIFI connected!");
  }
};


String urlEncode(const String &str) {
  String encoded = "";
  char c;
  char bufHex[4];
  for (size_t i = 0; i < str.length(); i++) {
    c = str[i];
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += c;
    } else {
      sprintf(bufHex, "%%%02X", (unsigned char)c);
      encoded += bufHex;
    }
  }
  return encoded;
}


void smsSend(const String destNumber, const char *smsMsg) {
  // WiFi 연결 상태 확인
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return;
  }
  String centrex_password = sha512(centrex_raw_password);
  // API 요청 URL 구성
  String url = String("https://") + centrexHost + "/RestApi/smssend?"
               + "id=" + urlEncode(centrex_id)
               + "&pass=" + urlEncode(centrex_password)
               + "&destnumber=" + urlEncode(destNumber)
               + "&smsmsg=" + urlEncode(smsMsg);  // smsMsg 사용
  // HTTPS 클라이언트 객체
  WiFiClientSecure client;
  client.setInsecure();  // 인증서 검증 생략 (프로덕션에선 CA 인증서 설정 권장)


  // 참고: smsmsg URL 인코딩 필요성 (한글/특수문자 포함 시)
  Serial.println("Request URL (from wifi_mqtt.cpp): " + url);

  // HTTP 요청 시작
  // HTTP 클라이언트 객체
  HTTPClient https;
  if (https.begin(client, url)) {
    int httpCode = https.POST("");  // 본문 없이 POST 요청
    if (httpCode > 0) {
      String payload = https.getString();
      Serial.printf("HTTP %d\nResponse: %s\n", httpCode, payload.c_str());
    } else {
      Serial.printf("POST failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();

  } else {
    Serial.println("Unable to connect");
  }
}