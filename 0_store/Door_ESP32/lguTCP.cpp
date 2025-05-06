#include "lguTCP.h"
#include "wifi_mqtt.h"
#include "variables.h"
#include "door.h"
WiFiServer tcpServer(TCP_PORT);  // 8001번 포트에서 TCP 서버 생성

void initTCPServer() {
  tcpServer.begin();  // TCP 서버 시작
  Serial.println("TCP 서버 시작! 포트: 8001");
}

void handleTCPClients() {
  WiFiClient tcpClient = tcpServer.available();  // 새로운 클라이언트 확인

  if (tcpClient) {
    Serial.println("입장확인");

    // 데이터 수신 대기 및 처리
    while (tcpClient.connected()) {
      if (tcpClient.available()) {
        String data = tcpClient.readStringUntil('\n');  // 줄바꿈 기준 데이터 읽기
        Serial.println("수신된 데이터: " + data);

        // 데이터 파싱
        int senderIndex = data.indexOf("sender=");
        if (senderIndex != -1) {
          String senderData = data.substring(senderIndex + 7);  // "sender=" 뒤의 데이터 추출
          int ampersandIndex = senderData.indexOf('&');         // '&' 위치 찾기
          String senderNumber;

          if (ampersandIndex != -1) {
            senderNumber = senderData.substring(0, ampersandIndex);  // '&' 이전까지 숫자 추출
          } else {
            senderNumber = senderData;  // '&'가 없으면 나머지 전체를 사용
          }

          senderNumber.trim();  // 공백 제거
          // Serial.println("Sender Number 값: " + senderNumber);  // 전화번호 출력
          mqttClient.publish(serverTopic, "SenderNumber/"+ senderNumber);
          OpenDoor();
        }
      }
    }

    // 클라이언트 연결 종료
    tcpClient.stop();
    // Serial.println("클라이언트 연결 종료");
  }
}
