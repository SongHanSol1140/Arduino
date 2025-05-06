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

    
    </style>
</head>

<body>
    <h1>Machine Setup Panel</h1>
    <section class="Temp">
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
                    alert('콜드브루 세정 설정 업데이트');
                }
            };
            xhttp.open('POST', '/setColdBrewClean', true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send('coldBrewCleanCount=' + newCount + '&coldBrewCleanTime=' + newTime);
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
  if (request->hasParam("scale1", true)) {
    Serial.println("스케일변경11");
    scale1 = request->getParam("scale1", true)->value().toInt();
    preferences.putInt("scale1", scale1);  // NVS에 저장
    initMachineValue();
  }
  if (request->hasParam("limitScale1", true)) {
    limitScale1 = request->getParam("limitScale1", true)->value().toInt();
    preferences.putInt("limitScale1", limitScale1);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetScale2(AsyncWebServerRequest *request) {
  Serial.println("스케일변경2");
  if (request->hasParam("scale2", true)) {
    Serial.println("스케일변경22");
    scale2 = request->getParam("scale2", true)->value().toInt();
    preferences.putInt("scale2", scale2);  // NVS에 저장
    initMachineValue();
  }
  if (request->hasParam("limitScale2", true)) {
    limitScale2 = request->getParam("limitScale2", true)->value().toInt();
    preferences.putInt("limitScale2", limitScale2);  // NVS에 저장
    initMachineValue();
  }
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
    preferences.putInt("limitLevelMin", limitLevelMin);  // NVS에 저장
    initMachineValue();
  }
  request->send(200, "text/html", "{\"status\":\"ok\"}");
}

void handleSetLevelLimit(AsyncWebServerRequest *request) {
  if (request->hasParam("limitLevel", true)) {
    limitLevel = request->getParam("limitLevel", true)->value().toInt();
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
  server.on("/setscale1", HTTP_POST, handleSetScale1);
  server.on("/setscale2", HTTP_POST, handleSetScale2);
  server.on("/setflowlimit1", HTTP_POST, handleSetFlowLimit1);
  server.on("/setflowlimit2", HTTP_POST, handleSetFlowLimit2);
  server.on("/setlevellimitmin", HTTP_POST, handleSetLevelLimitMin);
  server.on("/setlevellimit", HTTP_POST, handleSetLevelLimit);
  server.on("/setlevellimitmax", HTTP_POST, handleSetLevelLimitMax);
  server.on("/setdecafclean", HTTP_POST, handleSetDecafClean);
  server.on("/setcoldbrewclean", HTTP_POST, handleSetColdBrewClean);
  server.on("/settimer", HTTP_POST, handleSetTimer);
  server.begin();
  Serial.println("HTTP server started");
}