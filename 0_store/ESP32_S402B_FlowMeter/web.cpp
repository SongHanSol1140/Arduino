
#include "web.h"
#include "variables.h"
#include <WiFi.h>
#include <WebServer.h>

// 웹 서버 초기화
WebServer server(80);

// JSON 형태로 데이터 반환
void sendFlowData() {
    String json = "{";
    json += "\"time\":" + String(nowTime) + ",";
    json += "\"totalMilliLitres\":" + String(totalMilliLitres) + ",";
    json += "\"totalLitres\":" + String(totalMilliLitres / 1000.0);
    json += "}";
    server.send(200, "application/json", json);
}

// 지난 시간과 유량 초기화 함수
void resetFlowData() {
    nowTime = 0;
    totalMilliLitres = 0;
    server.send(200, "text/plain", "OK");
}

// HTML 페이지 렌더링 함수
void handleRoot() {
    String html = "<!DOCTYPE html><html>";
    html += "<head><meta charset='utf-8'><title>유량계 시스템</title>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
    html += "h1 { font-size: 72px; margin-bottom: 20px; }";
    html += "p { font-size: 60px; margin: 10px 0; }";
    html += "button { font-size: 60px; padding: 10px 20px; cursor: pointer; }";
    html += "</style>";
    html += "<script>";
    html += "function fetchData() {";
    html += "  fetch('/data').then(response => response.json()).then(data => {";
    html += "    document.getElementById('time').innerText = data.time + ' 초';";
    html += "    document.getElementById('total').innerText = data.totalMilliLitres + ' mL (' + data.totalLitres + ' L)';";
    html += "  });";
    html += "}";
    html += "function resetData() {";
    html += "  fetch('/reset').then(() => fetchData());";
    html += "}";
    html += "setInterval(fetchData, 1000);"; // 매초 데이터 갱신
    html += "</script></head>";
    html += "<body onload='fetchData()'><h1>유량계 데이터</h1>";
    html += "<p>지난 시간: <span id='time'>0 초</span></p>";
    html += "<p>총 유량: <span id='total'>0 mL (0 L)</span></p>";
    html += "<button onclick='resetData()'>데이터 초기화</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}


// 웹 서버 시작 함수
void startWebServer() {
    server.on("/", handleRoot);         // 메인 페이지
    server.on("/data", sendFlowData);   // JSON 데이터 반환
    server.on("/reset", resetFlowData); // 데이터 초기화

    server.begin();
    Serial.println("웹 서버 시작됨. IP: " + WiFi.localIP().toString());
}

void handleClientRequests() {
    server.handleClient();
}
