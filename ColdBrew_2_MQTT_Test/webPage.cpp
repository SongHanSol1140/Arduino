// webPage.cpp
#include "webPage.h"
#include "wifi_mqtt.h"
#include "switch.h"
#include "variables.h"

// 웹 서버 객체 생성
WebServer server(80);

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Controller</title>
    <style>
        * {
            box-sizing: border-box;
            border-collapse: collapse;
            padding: 0;
            margin: 0;
        }

        body {
            width: 100%;
            height: 100%;
            display: flex;
            flex-wrap: wrap;
        }

        h1 {
            width: 100%;
            height: 60px;
            display: flex;
            justify-content: center;
            align-items: center;
            background-color: #373737;
            color: white;
        }

        .buttons {
            width: 60%;
            display: flex;
            flex-wrap: wrap;
            border-right: 1px solid #ccc;
        }

        .settings {
            width: 40%;
        }

        .block {
            padding: 20px;
            width: 100%;
            display: flex;
            justify-content: center;
            flex-wrap: wrap;
            margin-bottom: 24px;
        }

        .block h2 {
            width: 100%;
            height: 50px;
            display: flex;
            justify-content: center;
            align-items: center;
            border-radius: 4px;
            margin-bottom: 0;
            background-color: #ccc;
        }

        .cleaning,
        .coffee {
            width: 100%;
            padding: 10px 5%;
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 0 5%;
        }

        .cleaning button,
        .coffee button {
            padding: 4px;
            height: 60px;
            border: none;
            background-color: #4CAF50;
            border-radius: 4px;
            font-size: 20px;
            font-weight: bold;
            color: #fff;
            margin-bottom: 10px;
        }

        .status-view {
            width: 100%;
            /* 테이블 경계를 하나로 결합 */
        }
       
    </style>
</head>

<body>
    <h1>Machine Status Panel</h1>
    <h1>Machine Control Panel</h1>
    <section class="buttons">

        <div class="block">
            <h2>추출</h2>
            <div class="coffee">
                <button onclick="startColdBrewExtraction(this)">콜드브루 추출</button>
                <button onclick="startColdBrewCooling(this)">콜드브루 냉각</button>
                <button onclick="startColdBrewTransfer(this)">콜드브루 이송</button>
        </div>
    </section>
    <script>
        function updateIndicator(indicator, status) {
            indicator.style.backgroundColor = status == 1 ? "green" : "red";
        }
        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);

                    var sensor1 = document.getElementById('sensor1');
                    var sensor2 = document.getElementById('sensor2');
                    var pid1 = document.getElementById('pid1');
                    var pid2 = document.getElementById('pid2');
                    var totalFlow1 = document.getElementById('totalFlow1');
                    var totalFlow2 = document.getElementById('totalFlow2');

                    var coolingStatus = document.getElementById('coolingStatus');
                    var systemStatus = document.getElementById('systemStatus');
                    var coffeeMachineStatus = document.getElementById('coffeeMachineStatus');

                    if (sensor1) sensor1.innerHTML = data.tmpInput1;
                    if (sensor2) sensor2.innerHTML = data.tmpInput2;
                    if (pid1) pid1.innerHTML = (data.tmpOutput1 * (3.3 / 255)).toFixed(2);
                    if (pid2) pid2.innerHTML = (data.tmpOutput2 * (3.3 / 255)).toFixed(2);
                    if (totalFlow1) totalFlow1.innerHTML = data.totalFlow1;
                    if (totalFlow2) totalFlow2.innerHTML = data.totalFlow2;
                }
            };
            xhttp.open('GET', '/status', true);
            xhttp.send();
        }

        window.onload = function () {
            getData(); // 페이지 로드 시 한 번 호출
            setInterval(getData, 500); // 매 초마다 호출하여 데이터 갱신
        }

        
        function disableButton(button) {
            button.disabled = true;
            setTimeout(function() {
                button.disabled = false;
            }, 3000); // 1초 후 버튼을 다시 활성화
        }

        function startColdBrewExtraction(button) {
            disableButton(button);
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Extraction started');
                }
            };
            xhttp.open('GET', '/coldbrew-extraction', true);
            xhttp.send();
        }
        function startColdBrewCooling(button) {
            disableButton(button);
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Cooling started');
                }
            };
            xhttp.open('GET', '/coldbrew-cooling', true);
            xhttp.send();
        }
        function startColdBrewTransfer(button) {
            disableButton(button);
            console.log("콜드브루 이송");
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Transfer started');
                }
            };
            xhttp.open('GET', '/coldbrew-transfer', true);
            xhttp.send();
        }
    </script>
</body>

</html>
)rawliteral";



void handleRoot() {
  String html = index_html;
  html.replace("%TMPINPUT1%", String(tmpInput1));
  html.replace("%TMPINPUT2%", String(tmpInput2));
  html.replace("%SETTMPPOINT1%", String(setTmpPoint1));
  html.replace("%SETTMPPOINT2%", String(setTmpPoint2));
  html.replace("%TMPOUTPUT1%", String(tmpOutput1 * (3.3 / 255), 1));
  html.replace("%TMPOUTPUT2%", String(tmpOutput2 * (3.3 / 255), 1));
  html.replace("%TMPOUTPUTLIMIT1%", String(tmpOutLimit1));
  html.replace("%TMPOUTPUTLIMIT2%", String(tmpOutLimit2));
  html.replace("%FLOWLIMIT1%", String(flowLimit1));
  html.replace("%TOTALFLOW1%", String(totalFlow1));
  html.replace("%FLOWLIMIT2%", String(flowLimit2));
  html.replace("%TOTALFLOW2%", String(totalFlow2));
  html.replace("%DECAFCLEANCOUNT%", String(decafCleanCount));
  html.replace("%DECAFCLEANTIME%", String(decafCleanTime));
  html.replace("%COLDBREWCLEANCOUNT%", String(cbCleanCount));
  html.replace("%COLDBREWCLEANTIME%", String(cbCleanTime));
  server.send(200, "text/html", html);
}

void handleStatus() {
  String json = "{";
  json += "\"tmpInput1\":" + String(tmpInput1) + ",";
  json += "\"setTmpPoint1\":" + String(setTmpPoint1) + ",";
  json += "\"tmpOutLimit1\":" + String(tmpOutLimit1) + ",";
  json += "\"tmpOutput1\":" + String(tmpOutput1) + ",";

  json += "\"tmpInput2\":" + String(tmpInput2) + ",";
  json += "\"setTmpPoint2\":" + String(setTmpPoint2) + ",";
  json += "\"tmpOutLimit2\":" + String(tmpOutLimit2) + ",";
  json += "\"tmpOutput2\":" + String(tmpOutput2) + ",";

  json += "\"flowLimit1\":" + String(flowLimit1) + ",";
  json += "\"totalFlow1\":" + String(totalFlow1) + ",";

  json += "\"flowLimit2\":" + String(flowLimit2) + ",";
  json += "\"totalFlow2\":" + String(totalFlow2) + ",";

  json += "\"decafCleanCount\":" + String(decafCleanCount) + ",";
  json += "\"decafCleanTime\":" + String(decafCleanTime) + ",";

  json += "\"coldBrewCleanCount\":" + String(cbCleanCount) + ",";
  json += "\"coldBrewCleanTime\":" + String(cbCleanTime) + ",";

  json += "\"coolingStatus\":" + String(coolingStatus ? true : false) + ",";
  json += "\"systemStatus\":" + String(systemStatus ? true : false) + ",";
  json += "\"coffeeMachineStatus\":" + String(coffeeMachineStatus ? true : false);

  json += "}";
  server.send(200, "application/json", json);
  // Serial.println(json);
}

// 콜드브루 추출
void handleColdBrewExtraction() {
  Serial.println("콜드브루 추출 버튼");
  orderColdBrewExtraction();
  server.send(200, "text/html", "{\"status\":\"ok\"}");
};
// 콜드브루 추출
void handleColdBrewCooling() {
  Serial.println("콜드브루 냉각 버튼");
  orderColdBrewCooling();
  server.send(200, "text/html", "{\"status\":\"ok\"}");
};
// 콜드브루 이송
void handleColdBrewTransfer() {
  Serial.println("콜드브루 이송 버튼");
  orderColdBrewTransfer();
  server.send(200, "text/html", "{\"status\":\"ok\"}");
};
void setupWebPage() {
  // 루트 URL 처리기 등록
  server.on("/", handleRoot);
  // 각 기능 URL 처리기 등록
  server.on("/coldbrew-extraction", handleColdBrewExtraction);
  server.on("/coldbrew-cooling", handleColdBrewCooling);
  server.on("/coldbrew-transfer", handleColdBrewTransfer);

  server.on("/status", handleStatus);    


  // 웹 서버 시작
  server.begin();
  Serial.println("HTTP server started");
}
