//webPage.h
#include "wifiSetup.h"
#include <EEPROM.h>

int sec1 = 0;
int sec2 = 0;
int sec3 = 0;
// Timer
int timerSet1 = 0;
int timerSet2 = 0;
int timerSet3 = 0;

void timerSetup();
void setTimerTime();
void initWebServer();
void handle_root();

// HTML 페이지
#if 1
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
  <meta charset="UTF-8"><!-- 한글을 출력하기 위한 인코딩설정 -->
  <style>
    li{
      list-style: none;
    }
    button{
      font-weight: bold;
      font-size: 24px;
      padding: 8px;
      border-radius: 12px;
      border: 2px solid #000;
    }
    input{
      font-size: 24px;
      padding: 8px;
      border-radius: 4px;
    }
  </style>
</head>

<body>
  <section class="title">
    <h2>ESP32 Web Server</h1>
  </section>

  <script>
    function setTimerTime(num){
      var sec = document.getElementById("sec").value;
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          alert(num + "번 타이머 변경 완료!");
          window.location.reload(); // 페이지 새로고침
        }
      };
      xhr.open("GET", "/settimer?sec=" + sec + "&num=" + num, true);
      xhr.send();
    }
    function validateAndSetTimerTime(num) {
      var sec = document.getElementById("sec").value;

      // 입력 값이 비어있거나 0보다 작거나 같은 경우 오류 메시지를 출력합니다.
      if (sec === '' || sec < 0) {
        alert("값을 다시 입력해주세요");
        window.location.reload(); // 페이지 새로고침
        return; // 함수 실행을 여기서 종료합니다.
      }

      // 입력 값이 유효한 경우 setTimerTime 함수를 호출합니다.
      setTimerTime(num);
    }
    

  </script>

  <section>
    <h2>타이머 설정(초)</h2>
    <ul>
      <li>
        <input type="number" id="sec" value="" placeholder="SEC"/>
      </li>
      <li>
        <button onclick="validateAndSetTimerTime(1)">1번 타이머 설정</button>
        <button onclick="validateAndSetTimerTime(2)">2번 타이머 설정</button>
        <button onclick="validateAndSetTimerTime(3)">3번 타이머 설정</button>
      </li>
    </ul>
  </section>

</body>
</html>
)rawliteral";
#endif

void handle_root(){
  server.send(200, "text/html", index_html);
}

void setTimerTime() {
  String secStr = server.arg("sec");
  String numStr = server.arg("num");
  int num = numStr.toInt();
  int sec = secStr.toInt();
  switch(num){
    case 1:
      sec1 = sec;
      timerSet1 = sec1 * 1000;
      Serial.println("타이머 시간설정 1 - " + secStr + "초");
      EEPROM.write(0, sec1 & 0xFF);
      EEPROM.write(1, (sec1 >> 8) & 0xFF);
      EEPROM.commit();
      break;
    case 2:
      sec2 = sec;
      timerSet2 = sec2 * 1000;
      Serial.println("타이머 시간설정 2 - " + secStr + "초");
      EEPROM.write(2, sec2 & 0xFF);
      EEPROM.write(3, (sec2 >> 8) & 0xFF);
      EEPROM.commit();
      break;
    case 3:
      sec3 = sec;
      timerSet3 = sec3 * 1000;
      Serial.println("타이머 시간설정 3 - " + secStr + "초");
      EEPROM.write(4, sec3 & 0xFF);
      EEPROM.write(5, (sec3 >> 8) & 0xFF);
      EEPROM.commit();
      break;
  }
  server.send(200, "text/html", index_html);
}

void initWebServer(){
  server.on("/", handle_root);
  server.on("/settimer", HTTP_GET, setTimerTime);
  server.begin();
}


void timerSetup(){
  EEPROM.begin(32); // EEPROM에 32바이트 할당
  sec1 = EEPROM.read(0) | (EEPROM.read(1) << 8); 
  sec2 = EEPROM.read(2) | (EEPROM.read(3) << 8); 
  sec3 = EEPROM.read(4) | (EEPROM.read(5) << 8);
  timerSet1 = sec1 * 1000;
  timerSet2 = sec2 * 1000;
  timerSet3 = sec3 * 1000;

  // if(timerSet1 == 255000){
  //   timerSet1 = 10000;
  // }
  // if(timerSet2 == 500000){
  //   timerSet2 = 300000;
  // }
  // if(timerSet3 == 255000){
  //   timerSet3 = 300000;
  // }
  Serial.println(timerSet1);
  Serial.println(timerSet2);
  Serial.println(timerSet3);
}