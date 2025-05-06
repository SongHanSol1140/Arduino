// webPage.h
#include "wifiSetup.h"
#include "weightCheck.h"

void handle_root();
void reset();
void setZeroScale();
void initWebServer();
void setTolerance();

// HTML 페이지
#if 1
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
  <meta charset="UTF-8"><!-- 한글을 출력하기 위한 인코딩설정 -->
  <style>
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
    <script>
        function reset() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/reset", true);
            xhr.send();
        }

        function zeroScale() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/zeroscale", true);
            xhr.send();
        }

        function setCalibrationFactor() {
            var calibrationFactor = document.getElementById('calibrationFactor').value;
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/setCalibrationFactor?value=" + calibrationFactor, true);
            xhr.send();
        }
    </script>
    <section class="title">
        <h2>ESP32 Load Cell</h1>
    </section>
    <section>
        <h2>로드셀 재시작</h2>
        <p>
            <button onclick="reset()">재부팅</button>
        </p>
    </section>
    <section>
        <p>
            <button onclick="zeroScale()">영점잡기</button>
        </p>
    </section>
        <section>
        <h2>calibrationFactor보정값 설정</h2>
        <p>
            <input id="calibrationFactor" type="number" step="0.01" />
            <button onclick="setCalibrationFactor()">설정</button>
        </p>
    </section>



</body>
</html>
)rawliteral";
#endif


void handle_root(){
  server.send(200, "text/html", index_html);
}

void reset(){
  ESP.restart();
}

void setZeroScale(){
  Serial.println("수동 영점 잡기");
  zeroFactor = average;
  Serial.println(zeroFactor);
  server.send(200, "text/html", index_html);
}


void setCalibrationFactor() {
  if (server.hasArg("value")) {
    calibration_factor = server.arg("value").toFloat();
    Serial.print("Calibration Factor 설정: ");
    Serial.println(calibration_factor);
  }
  server.send(200, "text/html", index_html);
}
void initWebServer(){
  server.on("/", handle_root);
  server.on("/zeroscale", HTTP_GET, setZeroScale);
  server.on("/reset", HTTP_GET, reset);
  server.on("/setCalibrationFactor", HTTP_GET, setCalibrationFactor);
  server.begin();
}