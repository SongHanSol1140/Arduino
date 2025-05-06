#include "web_server.h"
#include "variables.h"
#include "wifi_mqtt.h"
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
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
        h1 {
            width: 100%;
            height: 60px;
            display: flex;
            justify-content: center;
            align-items: center;
            background-color: #373737;
            color: white;
        }

        section{
            width: 100%;
            display: flex;
            flex-wrap: wrap; /* 수정된 부분 */
        }
        .block {
            width: calc(100% / 2 - 20px);
            display: flex;
            flex-wrap: wrap; /* 수정된 부분 */
            border: 1px solid #000;
            margin: 10px;
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

        .block div {
            width: 50%;
            padding: 10px;
            box-sizing: border-box;
        }
    </style>
</head>

<body>
    <h1>Machine Setup Panel</h1>
    <section>
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
                <p>순환량 : <span id="totalFlow1">%TOTALFLOW1%</span> ml</p>
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
        <div class="block">
            <h2>CT 스케일 설정</h2>
            <div>
                <h3>CT #1</h3>        
                <p>스케일1 : <input type="number" id="inputScale1" value="%SCALE1%"></p>
                <p>스케일 제한 : <input type="number" id="inputLimitScale1" value="%LIMITSCALE1%"></p>
                <p>변환된 전압% : <span id="convertedScale1">%CONVERTEDSCALE1%</span></p>
                <button class="submitButton" onclick="setScale1(event)">Set Scale 1</button>
            </div>
            <div>
                <h3>CT #2</h3>        
                <p>스케일2 : <input type="number" id="inputScale2" value="%SCALE2%"></p>
                <p>스케일 제한 : <input type="number" id="inputLimitScale2" value="%LIMITSCALE2%"></p>
                <p>변환된 전압% : <span id="convertedScale2">%CONVERTEDSCALE2%</span></p>
                <button class="submitButton" onclick="setScale2(event)">Set Scale 2</button>
            </div>

        </div>
        <div class="block">
            <h2>레벨 설정</h2>
            <div>
                <h3>디카페인 레벨 설정</h3>
                <p>디카페인 레벨 : <span id="decafLevel">%DECAFLEVEL%</span></p>
                <p>레벨 제한 : <input type="number" id="limitLevel" value="%limitLevel%"></p>
                <button class="submitButton" onclick="setLevelLimit(event)">Set Level Limit Min</button>

                <p>레벨 하한 설정 : <input type="number" id="limitLevelMin" value="%limitLevelMin%"></p>
                <button class="submitButton" onclick="setLevelLimitMin(event)">Set Level Limit</button>

                <p>레벨 상한 설정 : <input type="number" id="limitLevelMax" value="%limitLevelMax%"></p>
                <button class="submitButton" onclick="setLevelLimitMax(event)">Set Level Limit Max</button>
            </div>
            <div>
                <h3>콜드브루 센서감지</h3>
                <p>콜드브루 감지 : <span id="coldbrewLevel">%COLDBREWLEVEL%</span></p>
            </div>
        </div>
        <div class="block">
            <h2>타이머 설정</h2>
            <div>
                <h3>타이머설정</h3>
                <p>타이머 1 : <input type="number" id="inputTimer1" value="%TIMER1%"></p>
                <button class="submitButton" onclick="setTimer1(event)">Set Timer 1</button>
                <p>타이머 2 : <input type="number" id="inputTimer2" value="%TIMER2%"></p>
                <button class="submitButton" onclick="setTimer2(event)">Set Timer 2</button>
                <p>타이머 3 : <input type="number" id="inputTimer3" value="%TIMER3%"></p>
                <button class="submitButton" onclick="setTimer3(event)">Set Timer 3</button>
                <p>타이머 4 : <input type="number" id="inputTimer4" value="%TIMER4%"></p>
                <button class="submitButton" onclick="setTimer4(event)">Set Timer 4</button>
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

                    var coolingStatus = document.getElementById('coolingStatus');

                    if (sensor1) sensor1.innerHTML = data.tmpInput1;
                    if (sensor2) sensor2.innerHTML = data.tmpInput2;
                    if (pid1) pid1.innerHTML = (data.tmpOutput1 * (3.3 / 255)).toFixed(2);
                    if (pid2) pid2.innerHTML = (data.tmpOutput2 * (3.3 / 255)).toFixed(2);
                    if (totalFlow1) totalFlow1.innerHTML = data.totalFlow1;
                    if (totalFlow2) totalFlow2.innerHTML = data.totalFlow2;
                    if (convertedScale1) convertedScale1.innerHTML = data.convertedScale1;
                    if (convertedScale2) convertedScale2.innerHTML = data.convertedScale2;
                    if (decafLevel) decafLevel.innerHTML = data.decafLevel;
                    if (coldbrewLevel) coldbrewLevel.innerHTML = data.coldbrewLevel;
                }
            };
            xhttp.open('GET', '/data', true);
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
                    alert('콜드브루 세정 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setColdBrewClean', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('coldBrewCleanCount=' + newCount + '&coldBrewCleanTime=' + newTime);
        }

        function setScale1(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newScale = document.getElementById('inputScale1').value;
            var newLimit = document.getElementById('inputLimitScale1').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('스케일1 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setScale1', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('inputScale1=' + newScale + '&inputLimitScale1=' + newLimit);
        }

        function setScale2(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newScale = document.getElementById('inputScale2').value;
            var newLimit = document.getElementById('inputLimitScale2').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('스케일2 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setScale2', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('inputScale2=' + newScale + '&inputLimitScale2=' + newLimit);
        }

        function setLevelLimitMin(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newLimitMin = document.getElementById('limitLevelMin').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('레벨 최소 제한 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setLevelLimitMin', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('limitLevelMin=' + newLimitMin);
        }

        function setLevelLimit(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newLimit = document.getElementById('limitLevel').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('레벨 제한 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setLevelLimit', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('limitLevel=' + newLimit);
        }

        function setLevelLimitMax(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newLimitMax = document.getElementById('limitLevelMax').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('레벨 최대 제한 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setLevelLimitMax', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('limitLevelMax=' + newLimitMax);
        }

        function setTimer1(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTimer = document.getElementById('inputTimer1').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('타이머1 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTimer', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('timer1=' + newTimer);
        }

        function setTimer2(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTimer = document.getElementById('inputTimer2').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('타이머2 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTimer', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('timer2=' + newTimer);
        }

        function setTimer3(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTimer = document.getElementById('inputTimer3').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('타이머3 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTimer', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('timer3=' + newTimer);
        }

        function setTimer4(event) {
            event.preventDefault();
            var xhttp = new XMLHttpRequest();
            var newTimer = document.getElementById('inputTimer4').value;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    alert('타이머4 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setTimer', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('timer4=' + newTimer);
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
  html.replace("%SCALE1%", String(scale1));
  html.replace("%LIMITSCALE1%", String(limitScale1));
  html.replace("%CONVERTEDSCALE1%", String(convertedScale1));
  html.replace("%SCALE2%", String(scale2));
  html.replace("%LIMITSCALE2%", String(limitScale2));
  html.replace("%CONVERTEDSCALE2%", String(convertedScale2));
  html.replace("%FLOWRATE1%", String(FlowRate1, 1));
  html.replace("%FLOWLIMIT1%", String(flowLimit1));
  html.replace("%TOTALFLOW1%", String(totalFlow1));
  html.replace("%FLOWRATE2%", String(FlowRate2, 1));
  html.replace("%FLOWLIMIT2%", String(flowLimit2));
  html.replace("%TOTALFLOW2%", String(totalFlow2));
  html.replace("%DECAFLEVEL%", String(decafLevel));
  html.replace("%COLDBREWLEVEL%", String(coldbrewLevel));
  html.replace("%limitLevel%", String(limitLevel));
  html.replace("%limitLevelMin%", String(limitLevelMin));
  html.replace("%limitLevelMax%", String(limitLevelMax));
  html.replace("%DECAFCLEANCOUNT%", String(decafCleanCount));
  html.replace("%DECAFCLEANTIME%", String(decafCleanTime));
  html.replace("%COLDBREWCLEANCOUNT%", String(cbCleanCount));
  html.replace("%COLDBREWCLEANTIME%", String(cbCleanTime));
  html.replace("%TIMER1%", String(timer1));
  html.replace("%TIMER2%", String(timer2));
  html.replace("%TIMER3%", String(timer3));
  html.replace("%TIMER4%", String(timer4));
  request->send(200, "text/html", html);
}


void handleData(AsyncWebServerRequest *request) {
  String json = "{\"tmpInput1\":" + String(tmpInput1) + ",\"tmpInput2\":" + String(tmpInput2) + ",\"setTmpPoint1\":" + String(setTmpPoint1, 1) + ",\"setTmpPoint2\":" + String(setTmpPoint2, 1) + ",\"tmpOutLimit2\":" + String(tmpOutLimit2, 1) + ",\"tmpOutLimit1\":" + String(tmpOutLimit1, 1) + ",\"tmpOutput1\":" + String(tmpOutput1) + ",\"tmpOutput2\":" + String(tmpOutput2) + ",\"scale1\":" + String(scale1) + ",\"limitScale1\":" + String(limitScale1) + ",\"convertedScale1\":" + String(convertedScale1) + ",\"scale2\":" + String(scale2) + ",\"limitScale2\":" + String(limitScale2) + ",\"convertedScale2\":" + String(convertedScale2) + ",\"FlowRate1\":" + String(FlowRate1, 1) + ",\"flowLimit1\":" + String(flowLimit1) + ",\"totalFlow1\":" + String(totalFlow1) + ",\"FlowRate2\":" + String(FlowRate2, 1) + ",\"flowLimit2\":" + String(flowLimit2) + ",\"totalFlow2\":" + String(totalFlow2) + ",\"decafLevel\":" + String(decafLevel) + ",\"coldbrewLevel\":" + String(coldbrewLevel) + ",\"limitLevel\":" + String(limitLevel) + ",\"limitLevelMin\":" + String(limitLevelMin) + ",\"limitLevelMax\":" + String(limitLevelMax) + ",\"decafCleanCount\":" + String(decafCleanCount) + ",\"decafCleanTime\":" + String(decafCleanTime) + ",\"coldBrewCleanCount\":" + String(cbCleanCount) + ",\"coldBrewCleanTime\":" + String(cbCleanTime) + ",\"timer1\":" + String(timer1) + ",\"timer2\":" + String(timer2) + ",\"timer3\":" + String(timer3) + ",\"timer4\":" + String(timer4) + "}";
  request->send(200, "application/json", json);
}

void handleTmpSet1(AsyncWebServerRequest *request) {
  if (request->hasParam("setTmpPoint1", true)) {
    setTmpPoint1 = request->getParam("setTmpPoint1", true)->value().toDouble();
    Serial.println(setTmpPoint1);
    preferences.putDouble("setTmpPoint1", setTmpPoint1);
    initMachineValue();
  }
  if (request->hasParam("tmpOutLimit1", true)) {
    tmpOutLimit1 = request->getParam("tmpOutLimit1", true)->value().toDouble();
    if (tmpOutLimit1 > 100) { tmpOutLimit1 = 100; };
    Serial.println(tmpOutLimit1);
    preferences.putDouble("tmpOutLimit1", tmpOutLimit1);
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleTmpSet2(AsyncWebServerRequest *request) {
  if (request->hasParam("setTmpPoint2", true)) {
    setTmpPoint2 = request->getParam("setTmpPoint2", true)->value().toDouble();
    Serial.println(setTmpPoint2);
    preferences.putDouble("setTmpPoint2", setTmpPoint2);
    initMachineValue();
  }
  if (request->hasParam("tmpOutLimit2", true)) {
    tmpOutLimit2 = request->getParam("tmpOutLimit2", true)->value().toDouble();
    if (tmpOutLimit2 > 100) { tmpOutLimit2 = 100; };
    Serial.println(tmpOutLimit2);
    preferences.putDouble("tmpOutLimit2", tmpOutLimit2);
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetScale1(AsyncWebServerRequest *request) {
  Serial.println("스케일변경1");
  if (request->hasParam("inputScale1", true)) {
    scale1 = request->getParam("inputScale1", true)->value().toInt();
    Serial.println(scale1);
    preferences.putInt("scale1", scale1);  // NVS에 저장
  }
  if (request->hasParam("inputLimitScale1", true)) {
    limitScale1 = request->getParam("inputLimitScale1", true)->value().toInt();
    Serial.println(limitScale1);
    preferences.putInt("limitScale1", limitScale1);  // NVS에 저장
  }
  initMachineValue();
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetScale2(AsyncWebServerRequest *request) {
  Serial.println("스케일변경2");
  if (request->hasParam("inputScale2", true)) {
    scale2 = request->getParam("inputScale2", true)->value().toInt();
    Serial.println(scale2);
    preferences.putInt("scale2", scale2);  // NVS에 저장
  }
  if (request->hasParam("inputLimitScale2", true)) {
    limitScale2 = request->getParam("inputLimitScale2", true)->value().toInt();
    Serial.println(limitScale2);
    preferences.putInt("limitScale2", limitScale2);  // NVS에 저장
  }
  initMachineValue();
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetFlowLimit1(AsyncWebServerRequest *request) {
  Serial.println("handleSetFlowLimit1 called");

  if (request->hasParam("flowLimit1", true)) {
    flowLimit1 = request->getParam("flowLimit1", true)->value().toInt();
    Serial.println("flowLimit1: " + String(flowLimit1));
    preferences.putInt("flowLimit1", flowLimit1);  // NVS에 저장
    initMachineValue();
  } else {
    Serial.println("flowLimit1 not received");
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetFlowLimit2(AsyncWebServerRequest *request) {
  Serial.println("handleSetFlowLimit2 called");

  if (request->hasParam("flowLimit2", true)) {
    flowLimit2 = request->getParam("flowLimit2", true)->value().toInt();
    Serial.println("flowLimit2: " + String(flowLimit2));
    preferences.putInt("flowLimit2", flowLimit2);  // NVS에 저장
    initMachineValue();
  } else {
    Serial.println("flowLimit2 not received");
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetLevelLimitMin(AsyncWebServerRequest *request) {
  if (request->hasParam("limitLevelMin", true)) {
    limitLevelMin = request->getParam("limitLevelMin", true)->value().toInt();
    Serial.println(limitLevelMin);
    preferences.putInt("limitLevelMin", limitLevelMin);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetLevelLimit(AsyncWebServerRequest *request) {
  if (request->hasParam("limitLevel", true)) {
    limitLevel = request->getParam("limitLevel", true)->value().toInt();
    Serial.println(limitLevel);
    preferences.putInt("limitLevel", limitLevel);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetLevelLimitMax(AsyncWebServerRequest *request) {
  if (request->hasParam("limitLevelMax", true)) {
    limitLevelMax = request->getParam("limitLevelMax", true)->value().toInt();
    preferences.putInt("limitLevelMax", limitLevelMax);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetDecafClean(AsyncWebServerRequest *request) {
  if (request->hasParam("decafCleanCount", true)) {
    decafCleanCount = request->getParam("decafCleanCount", true)->value().toInt();
    preferences.putInt("decafCleanCount", decafCleanCount);  // NVS에 저장
    initMachineValue();
  }
  if (request->hasParam("decafCleanTime", true)) {
    decafCleanTime = request->getParam("decafCleanTime", true)->value().toInt();
    preferences.putInt("decafCleanTime", decafCleanTime);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetColdBrewClean(AsyncWebServerRequest *request) {
  if (request->hasParam("coldBrewCleanCount", true)) {
    cbCleanCount = request->getParam("coldBrewCleanCount", true)->value().toInt();
    preferences.putInt("cbCleanCount", cbCleanCount);  // NVS에 저장
    initMachineValue();
  }
  if (request->hasParam("coldBrewCleanTime", true)) {
    cbCleanTime = request->getParam("coldBrewCleanTime", true)->value().toInt();
    preferences.putInt("coldBrewCleanTime", cbCleanTime);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetTimer(AsyncWebServerRequest *request) {
  if (request->hasParam("timer1", true)) {
    timer1 = request->getParam("timer1", true)->value().toInt();
    preferences.putInt("timer1", timer1);
  }
  if (request->hasParam("timer2", true)) {
    timer2 = request->getParam("timer2", true)->value().toInt();
    preferences.putInt("timer2", timer2);
  }
  if (request->hasParam("timer3", true)) {
    timer3 = request->getParam("timer3", true)->value().toInt();
    preferences.putInt("timer3", timer3);
  }
  if (request->hasParam("timer4", true)) {
    timer4 = request->getParam("timer4", true)->value().toInt();
    preferences.putInt("timer4", timer4);
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void setWebPage() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.on("/setTmpPoint1", HTTP_POST, handleTmpSet1);
  server.on("/setTmpPoint2", HTTP_POST, handleTmpSet2);
  server.on("/setScale1", HTTP_POST, handleSetScale1);
  server.on("/setScale2", HTTP_POST, handleSetScale2);
  server.on("/setFlowLimit1", HTTP_POST, handleSetFlowLimit1);
  server.on("/setFlowLimit2", HTTP_POST, handleSetFlowLimit2);
  server.on("/setLevelLimitMin", HTTP_POST, handleSetLevelLimitMin);
  server.on("/setLevelLimit", HTTP_POST, handleSetLevelLimit);
  server.on("/setLevelLimitMax", HTTP_POST, handleSetLevelLimitMax);
  server.on("/setDecafClean", HTTP_POST, handleSetDecafClean);
  server.on("/setColdBrewClean", HTTP_POST, handleSetColdBrewClean);
  server.on("/setTimer", HTTP_POST, handleSetTimer);
  server.begin();
  Serial.println("HTTP server started");
}