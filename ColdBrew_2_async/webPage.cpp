// webPage.cpp
#include "webPage.h"
#include "wifi_mqtt.h"
#include "switch.h"
#include "variables.h"

// 웹 서버 객체 생성
AsyncWebServer server(80);

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
        .status-table{
            width: 100%;
        }

        .status {
            width: 20%;
            display: table-cell;
            border: 1px solid #000;
            text-align: center;
        }

        .status p {
            font-size: 20px;
            margin: 5px 0;
        }

        .status-indicator {
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background-color: red;
            margin: 5px auto;
        }
    </style>
</head>

<body>
    <h1>Machine Status Panel</h1>
    <section class="status-view">
        <table class = "status-table">
            <tr>
                <td class="status">
                    <p># 3</p>
                    <div class="status-indicator" id="hash3Indicator"></div>
                </td>
                <td class="status">
                    <p># 5</p>
                    <div class="status-indicator" id="hash5Indicator"></div>
                </td>
                <td class="status">
                    <p># 6</p>
                    <div class="status-indicator" id="hash6Indicator"></div>
                </td>
                <td class="status">
                    <p># 8</p>
                    <div class="status-indicator" id="hash8Indicator"></div>
                </td>
                <td class="status">
                    <p># 9</p>
                    <div class="status-indicator" id="hash9Indicator"></div>
                </td>
            </tr>
            <tr>
                <td class="status">
                    <p># 11</p>
                    <div class="status-indicator" id="hash11Indicator"></div>
                </td>
                <td class="status">
                    <p># 12</p>
                    <div class="status-indicator" id="hash12Indicator"></div>
                </td>
                <td class="status">
                    <p># 13</p>
                    <div class="status-indicator" id="hash13Indicator"></div>
                </td>
                <td class="status">
                    <p># 14</p>
                    <div class="status-indicator" id="hash14Indicator"></div>
                </td>
                <td class="status">
                    <p># 15</p>
                    <div class="status-indicator" id="hash15Indicator"></div>
                </td>
            </tr>
            <tr>
                <td class="status">
                    <p># 16</p>
                    <div class="status-indicator" id="hash16Indicator"></div>
                </td>
                <td class="status">
                    <p># 20</p>
                    <div class="status-indicator" id="hash20Indicator"></div>
                </td>
                <td class="status">
                    <p># 21</p>
                    <div class="status-indicator" id="hash21Indicator"></div>
                </td>
                <td class="status">
                    <p># 22</p>
                    <div class="status-indicator" id="hash22Indicator"></div>
                </td>
                <td class="status">
                    <p># 24</p>
                    <div class="status-indicator" id="hash24Indicator"></div>
                </td>
            </tr>
            <tr>
                <td class="status">
                    <p># 25</p>
                    <div class="status-indicator" id="hash25Indicator"></div>
                </td>
                <td class="status">
                    <p># 26</p>
                    <div class="status-indicator" id="hash26Indicator"></div>
                </td>
                <td class="status">
                    <p> 냉각기 가동 여부</p>
                    <div class="status-indicator" id="coolingIndicator"></div>
                </td>
            </tr>
        </table>
    </section>
    <h1>Machine Control Panel</h1>
    <section class="buttons">
        <div class="block">
            <h2>세정</h2>
            <div class="cleaning">
                <button onclick="startCoffeeCleaning()">커피머신 세정</button>
                <button onclick="startCoffeeLowerCleaning()">커피머신 하단부 세정</button>
                <button onclick="startDecafCycleCleaning()">디카페인 사이클 세정</button>
                <button onclick="startColdBrewCleaning()">콜드브루 세정</button>
                <button onclick="startColdBrewLineCleaningOne()">콜드브루 라인1 세정</button>
                <button onclick="startColdBrewLineCleaningTwo()">콜드브루 라인2 세정</button>
            </div>
        </div>
        <div class="block">
            <h2>추출</h2>
            <div class="coffee">
                <button onclick="startBrewedExtraction()">브루드 추출</button>
                <button onclick="startBrewedCooling()">브루드 냉각</button>
                <button onclick="startBrewedTransfer()">브루드 이송</button>
                <button onclick="startColdBrewExtraction()">콜드브루 추출</button>
                <button onclick="startColdBrewCooling()">콜드브루 냉각</button>
                <button onclick="startColdBrewTransfer()">콜드브루 이송</button>
                <button onclick="startDecafExtraction()">디카페인 추출</button>
                <button onclick="startDecafCooling()">디카페인 냉각</button>
                <button onclick="startDecafTransfer()">디카페인 이송</button>
                <button onclick="startDecafTransferFromFridge()">디카페인 냉장고에서 이송</button>
            </div>
        </div>
    </section>
    <section class="settings">
        <div class="block">
            <h2>온도센서</h2>
            <div>
                <h3>디카페인 온도센서(#1)</h3>
                <p>현재 온도(PV): <span id="sensor1">%TMPINPUT1%</span> C</p>
                <p>목표 온도 : <input type="number" step="0.1" id="inputSetTmpPointInput1" value="%SETTMPPOINT1%"></p>
                <p>출력 제한 : <input type="number" step="0.1" id="inputTmpOutLimitInput1" value="%TMPOUTPUTLIMIT1%"></p>
                <p>PID 출력 : <span id="pid1">%TMPOUTPUT1%</span> V</p>
                <button class="submitButton" onclick="setSensor1(event)">Set Sensor 1</button>
            </div>
            <div>
                <h3>콜드브루 온도센서(#2)</h3>
                <p>현재 온도(PV): <span id="sensor2">%TMPINPUT2%</span> C</p>
                <p>목표 온도 : <input type="number" step="0.1" id="inputSetTmpPointInput2" value="%SETTMPPOINT2%"></p>
                <p>출력 제한 : <input type="number" step="0.1" id="inputTmpOutLimitInput2" value="%TMPOUTPUTLIMIT2%"></p>
                <p>PID 출력 : <span id="pid2">%TMPOUTPUT2%</span> V</p>
                <button class="submitButton" onclick="setSensor2(event)">Set Sensor 2</button>
            </div>
        </div>
        <div class="block">
            <h2>유량계 설정</h2>
            <div>
                <h3>순환 유량계</h3>
                <p>순환 제한 설정 : <input type="number" step="1" id="setFlowLimit1Input" value="%FLOWLIMIT1%"></p>
                <p>순환 : <span id="totalFlow1">%TOTALFLOW1%</span> ml</p>
                <button class="submitButton" onclick="setFlowLimit1(event)">Set Flow Limit 1</button>
            </div>
            <div>
                <h3>유입 유량계</h3>
                <p>유입 제한 설정 : <input type="number" step="1" id="setFlowLimit2Input" value="%FLOWLIMIT2%"></p>
                <p>유입량 : <span id="totalFlow2">%TOTALFLOW2%</span> ml</p>
                <button class="submitButton" onclick="setFlowLimit2(event)">Set Flow Limit 2</button>
            </div>
        </div>
        <div class="block">
            <h2>세정 설정</h2>
            <div>
                <h3>디카페인 세정 설정</h3>
                세정 횟수 : <input type="number" step="1" id="decafCleanCount" value="%DECAFCLEANCOUNT%"><br>
                세정 시간 : <input type="number" step="1" id="decafCleanTime" value="%DECAFCLEANTIME%"><br>
                <button class="submitButton" onclick="setDecafClean(event)">Set Decaf Clean</button>
            </div>
            <div>
                <h3>콜드브루 세정 설정</h3>
                세정 횟수: <input type="number" step="1" id="coldBrewCleanCount" value="%COLDBREWCLEANCOUNT%"><br>
                세정 시간: <input type="number" step="1" id="coldBrewCleanTime" value="%COLDBREWCLEANTIME%"><br>
                <button class="submitButton" onclick="setColdBrewClean(event)">Set Cold Brew Clean</button>
            </div>
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

                    var hash3Indicator = document.getElementById('hash3Indicator');
                    var hash5Indicator = document.getElementById('hash5Indicator');
                    var hash6Indicator = document.getElementById('hash6Indicator');
                    var hash8Indicator = document.getElementById('hash8Indicator');
                    var hash9Indicator = document.getElementById('hash9Indicator');
                    var hash11Indicator = document.getElementById('hash11Indicator');
                    var hash12Indicator = document.getElementById('hash12Indicator');
                    var hash13Indicator = document.getElementById('hash13Indicator');
                    var hash14Indicator = document.getElementById('hash14Indicator');
                    var hash15Indicator = document.getElementById('hash15Indicator');
                    var hash16Indicator = document.getElementById('hash16Indicator');
                    var hash20Indicator = document.getElementById('hash20Indicator');
                    var hash21Indicator = document.getElementById('hash21Indicator');
                    var hash22Indicator = document.getElementById('hash22Indicator');
                    var hash24Indicator = document.getElementById('hash24Indicator');
                    var hash25Indicator = document.getElementById('hash25Indicator');
                    var hash26Indicator = document.getElementById('hash26Indicator');
                    var coolingStatus = document.getElementById('coolingStatus');

                    if (sensor1) sensor1.innerHTML = data.tmpInput1;
                    if (sensor2) sensor2.innerHTML = data.tmpInput2;
                    if (pid1) pid1.innerHTML = (data.tmpOutput1 * (3.3 / 255)).toFixed(2);
                    if (pid2) pid2.innerHTML = (data.tmpOutput2 * (3.3 / 255)).toFixed(2);
                    if (totalFlow1) totalFlow1.innerHTML = data.totalFlow1;
                    if (totalFlow2) totalFlow2.innerHTML = data.totalFlow2;


                    console.log(data.hash13Status);
                    console.log(data.hash14Status);
                    console.log(data.hash5Status);
                    console.log(data.hash26Status);
                    console.log(data.coolingStatus);

                    updateIndicator(hash3Indicator, data.hash3Status);
                    updateIndicator(hash5Indicator, data.hash5Status);
                    updateIndicator(hash6Indicator, data.hash6Status);
                    updateIndicator(hash8Indicator, data.hash8Status);
                    updateIndicator(hash9Indicator, data.hash9Status);
                    updateIndicator(hash11Indicator, data.hash11Status);
                    updateIndicator(hash12Indicator, data.hash12Status);
                    updateIndicator(hash13Indicator, data.hash13Status);
                    updateIndicator(hash14Indicator, data.hash14Status);
                    updateIndicator(hash15Indicator, data.hash15Status);
                    updateIndicator(hash16Indicator, data.hash16Status);
                    updateIndicator(hash20Indicator, data.hash20Status);
                    updateIndicator(hash21Indicator, data.hash21Status);
                    updateIndicator(hash22Indicator, data.hash22Status);
                    updateIndicator(hash24Indicator, data.hash24Status);
                    updateIndicator(hash25Indicator, data.hash25Status);
                    updateIndicator(hash26Indicator, data.hash26Status);
                    updateIndicator(coolingIndicator, data.coolingStatus);
                }
            };
            xhttp.open('GET', '/status', true);
            xhttp.send();
        }

        window.onload = function () {
            getData(); // 페이지 로드 시 한 번 호출
            setInterval(getData, 500); // 매 초마다 호출하여 데이터 갱신
        }

        function setSensor1(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTarget = document.getElementById('inputSetTmpPointInput1').value;
            var newLimit = document.getElementById('inputTmpOutLimitInput1').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('온도센서1 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTmpPoint1', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('setTmpPoint1=' + newTarget + '&tmpOutLimit1=' + newLimit);
        }

        function setSensor2(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTarget = document.getElementById('inputSetTmpPointInput2').value;
            var newLimit = document.getElementById('inputTmpOutLimitInput2').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('온도센서2 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTmpPoint2', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('setTmpPoint2=' + newTarget + '&tmpOutLimit2=' + newLimit);
        }

        function setFlowLimit1(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newLimit = document.getElementById('setFlowLimit1Input').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('유량계1 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setFlowLimit1', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('flowLimit1=' + newLimit);
        }

        function setFlowLimit2(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newLimit = document.getElementById('setFlowLimit2Input').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('유량계2 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setFlowLimit2', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('flowLimit2=' + newLimit);
        }

        function setDecafClean(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newCount = document.getElementById('decafCleanCount').value;
            var newTime = document.getElementById('decafCleanTime').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('디카페인 세정설정 업데이트');
                }
            };
            xhttp.open('POST', '/setDecafClean', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('decafCleanCount=' + newCount + '&decafCleanTime=' + newTime);
        }

        function setColdBrewClean(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newCount = document.getElementById('coldBrewCleanCount').value;
            var newTime = document.getElementById('coldBrewCleanTime').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('콜드브루 세정설정 업데이트');
                }
            };
            xhttp.open('POST', '/setColdBrewClean', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('coldBrewCleanCount=' + newCount + '&coldBrewCleanTime=' + newTime);
        }

        function startCoffeeCleaning() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Coffee cleaning started');
                }
            };
            xhttp.open('GET', '/coffee-cleaning', true);
            xhttp.send();
        }

        function startCoffeeLowerCleaning() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Coffee lower cleaning started');
                }
            };
            xhttp.open('GET', '/coffee-lower-cleaning', true);
            xhttp.send();
        }

        function startDecafCycleCleaning() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Decaf cycle cleaning started');
                }
            };
            xhttp.open('GET', '/decaf-cycle-cleaning', true);
            xhttp.send();
        }

        function startColdBrewCleaning() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew  Cleaning started');
                }
            };
            xhttp.open('GET', '/coldbrew-cleaning', true);
            xhttp.send();
        }
        function startColdBrewLineCleaningOne() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Line One Cleaning started');
                }
            };
            xhttp.open('GET', '/coldbrew-line-one-cleaning', true);
            xhttp.send();
        }
        function startColdBrewLineCleaningTwo() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Line Two Cleaning started');
                }
            };
            xhttp.open('GET', '/coldbrew-line-two-cleaning', true);
            xhttp.send();
        }
        function startBrewedExtraction() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Brewed Extraction started');
                }
            };
            xhttp.open('GET', '/brewed-extraction', true);
            xhttp.send();
        }
        function startBrewedCooling() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Brewed Cooling started');
                }
            };
            xhttp.open('GET', '/brewed-cooling', true);
            xhttp.send();
        }
        function startBrewedTransfer() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Brewed Tansfer started');
                }
            };
            xhttp.open('GET', '/brewed-transfer', true);
            xhttp.send();
        }

        function startColdBrewExtraction() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Extraction started');
                }
            };
            xhttp.open('GET', '/coldbrew-extraction', true);
            xhttp.send();
        }
        function startColdBrewCooling() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('ColdBrew Cooling started');
                }
            };
            xhttp.open('GET', '/coldbrew-cooling', true);
            xhttp.send();
        }
        function startColdBrewTransfer() {
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

        function startDecafExtraction() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Decaf Extraction started');
                }
            };
            xhttp.open('GET', '/decaf-extraction', true);
            xhttp.send();
        }
        function startDecafCooling() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Decaf Cooling started');
                }
            };
            xhttp.open('GET', '/decaf-cooling', true);
            xhttp.send();
        }
        function startDecafTransfer() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Decaf Transfer started');
                }
            };
            xhttp.open('GET', '/decaf-transfer', true);
            xhttp.send();
        }
        function startDecafTransferFromFridge() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    // alert('Decaf Transfer started');
                }
            };
            xhttp.open('GET', '/decaf-transfer-from-fridge', true);
            xhttp.send();
        }
    </script>
</body>

</html>
)rawliteral";



void handleRoot(AsyncWebServerRequest *request) {
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
  request->send(200, "text/html", html);
}

void handleStatus(AsyncWebServerRequest *request) {
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

  json += "\"hash3Status\":" + String(digitalRead(hash3) ? true : false) + ",";
  json += "\"hash5Status\":" + String(digitalRead(hash5) ? true : false) + ",";
  json += "\"hash6Status\":" + String(digitalRead(hash6) ? true : false) + ",";
  json += "\"hash8Status\":" + String(digitalRead(hash8) ? true : false) + ",";
  json += "\"hash9Status\":" + String(digitalRead(hash9) ? true : false) + ",";
  json += "\"hash11Status\":" + String(digitalRead(hash11) ? true : false) + ",";
  json += "\"hash12Status\":" + String(digitalRead(hash12) ? true : false) + ",";
  json += "\"hash13Status\":" + String(digitalRead(hash13) ? true : false) + ",";
  json += "\"hash14Status\":" + String(digitalRead(hash14) ? true : false) + ",";
  json += "\"hash15Status\":" + String(digitalRead(hash15) ? true : false) + ",";
  json += "\"hash16Status\":" + String(digitalRead(hash16) ? true : false) + ",";
  json += "\"hash20Status\":" + String(digitalRead(hash20) ? true : false) + ",";
  json += "\"hash21Status\":" + String(digitalRead(hash21) ? true : false) + ",";
  json += "\"hash22Status\":" + String(digitalRead(hash22) ? true : false) + ",";
  json += "\"hash24Status\":" + String(digitalRead(hash24) ? true : false) + ",";
  json += "\"hash25Status\":" + String(digitalRead(hash25) ? true : false) + ",";
  json += "\"hash26Status\":" + String(digitalRead(hash26) ? true : false) + ",";
  json += "\"coolingStatus\":" + String(coolingStatus ? true : false);

  json += "}";
  request->send(200, "application/json", json);
}

void handleTmpSet1(AsyncWebServerRequest *request) {
  if (request->hasParam("setTmpPoint1", true)) {
    setTmpPoint1 = request->getParam("setTmpPoint1", true)->value().toDouble();
    Serial.println(setTmpPoint1);
    client.publish(coldbrewSetup, ("setTmpPoint1/" + String(setTmpPoint1)).c_str());
  }
  if (request->hasParam("tmpOutLimit1", true)) {
    tmpOutLimit1 = request->getParam("tmpOutLimit1", true)->value().toDouble();
    if (tmpOutLimit1 > 100) { tmpOutLimit1 = 100; }
    Serial.println(tmpOutLimit1);
    client.publish(coldbrewSetup, ("tmpOutLimit1/" + String(tmpOutLimit1)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleTmpSet2(AsyncWebServerRequest *request) {
  if (request->hasParam("setTmpPoint2", true)) {
    setTmpPoint2 = request->getParam("setTmpPoint2", true)->value().toDouble();
    Serial.println(setTmpPoint2);
    client.publish(coldbrewSetup, ("setTmpPoint2/" + String(setTmpPoint2)).c_str());
  }
  if (request->hasParam("tmpOutLimit2", true)) {
    tmpOutLimit2 = request->getParam("tmpOutLimit2", true)->value().toDouble();
    if (tmpOutLimit2 > 100) { tmpOutLimit2 = 100; }
    Serial.println(tmpOutLimit2);
    client.publish(coldbrewSetup, ("tmpOutLimit2/" + String(tmpOutLimit2)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleFlowLimit1(AsyncWebServerRequest *request) {
  if (request->hasParam("flowLimit1", true)) {
    flowLimit1 = request->getParam("flowLimit1", true)->value().toDouble();
    Serial.println(flowLimit1);
    client.publish(coldbrewSetup, ("flowLimit1/" + String(flowLimit1)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleFlowLimit2(AsyncWebServerRequest *request) {
  if (request->hasParam("flowLimit2", true)) {
    flowLimit2 = request->getParam("flowLimit2", true)->value().toDouble();
    Serial.println(flowLimit2);
    client.publish(coldbrewSetup, ("flowLimit2/" + String(flowLimit2)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleDecafClean(AsyncWebServerRequest *request) {
  if (request->hasParam("decafCleanCount", true)) {
    decafCleanCount = request->getParam("decafCleanCount", true)->value().toInt();
    Serial.println(decafCleanCount);
    client.publish(coldbrewSetup, ("decafCleanCount/" + String(decafCleanCount)).c_str());
  }
  if (request->hasParam("decafCleanTime", true)) {
    decafCleanTime = request->getParam("decafCleanTime", true)->value().toInt();
    Serial.println(decafCleanTime);
    client.publish(coldbrewSetup, ("decafCleanTime/" + String(decafCleanTime)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleColdBrewClean(AsyncWebServerRequest *request) {
  if (request->hasParam("coldBrewCleanCount", true)) {
    cbCleanCount = request->getParam("coldBrewCleanCount", true)->value().toInt();
    Serial.println(cbCleanCount);
    client.publish(coldbrewSetup, ("cbCleanCount/" + String(cbCleanCount)).c_str());
  }
  if (request->hasParam("coldBrewCleanTime", true)) {
    cbCleanTime = request->getParam("coldBrewCleanTime", true)->value().toInt();
    Serial.println(cbCleanTime);
    client.publish(coldbrewSetup, ("cbCleanTime/" + String(cbCleanTime)).c_str());
  }
  request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404: Not Found");
}

void handleCoffeeCleaning(AsyncWebServerRequest *request) {
  Serial.println("커피머신 세정 버튼");
  orderCoffeeCleaning();
  request->send(200, "text/plain", "Coffee Cleaning Started");
}

void setupWebPage() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/coffee-cleaning", HTTP_GET, handleCoffeeCleaning);
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/setTmpPoint1", HTTP_POST, handleTmpSet1);
  server.on("/setTmpPoint2", HTTP_POST, handleTmpSet2);
  server.on("/setFlowLimit1", HTTP_POST, handleFlowLimit1);
  server.on("/setFlowLimit2", HTTP_POST, handleFlowLimit2);
  server.on("/setDecafClean", HTTP_POST, handleDecafClean);
  server.on("/setColdBrewClean", HTTP_POST, handleColdBrewClean);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
