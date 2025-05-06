#include "lguTCP.h"
#include "wifi_mqtt.h"
#include "variables.h"

#include <WiFi.h>              // WiFi 상태 확인
#include <HTTPClient.h>        // HTTP 요청 라이브러리
#include <WiFiClientSecure.h>  // HTTPS 요청 라이브러리
WiFiServer tcpServer(8001);    // 8001번 포트에서 TCP 서버 생성
void initTCPServer() {
  tcpServer.begin();  // TCP 서버 시작
  Serial.println("TCP 서버 시작! 포트: 8001");
}

void handleTCPClients() {
  WiFiClient client = tcpServer.available();  // 새로운 클라이언트 확인
  String phoneNumber;
  if (client) {
    Serial.println("입장확인");
    // 데이터 수신 대기 및 처리
    while (client.connected()) {
      delay(1);
      if (client.available()) {
        String data = client.readStringUntil('\n');  // 줄바꿈 기준 데이터 읽기
        // Serial.println("수신된 데이터: " + data);

        // 데이터 파싱
        int senderIndex = data.indexOf("sender=");
        if (senderIndex != -1) {
          String senderData = data.substring(senderIndex + 7);  // "sender=" 뒤의 데이터 추출
          int ampersandIndex = senderData.indexOf('&');         // '&' 위치 찾기


          if (ampersandIndex != -1) {
            phoneNumber = senderData.substring(0, ampersandIndex);  // '&' 이전까지 숫자 추출
          } else {
            phoneNumber = senderData;  // '&'가 없으면 나머지 전체를 사용
          }

          phoneNumber.trim();  // 공백 제거
          Serial.println("발신자번호" + phoneNumber);
          smsSend(phoneNumber, msg);
        }
      }
    }

    // 클라이언트 연결 종료
    client.stop();
    delay(10);
  }
}
