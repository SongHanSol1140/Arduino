#include "webPage.h"
#include "variables.h"
#include "pwmControl.h"

AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "frequency";
const char* PARAM_INPUT_2 = "targetDuty";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP PWM Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    form{
      width: 500px;
    }
    input{
      border: 1px solid #000;
    }
  </style>
</head>
<body>
  <h2>PWM Control</h2>
  <form action="/get">
  <p>
    Frequency: <input type="number" name="frequency" value="%FREQUENCY%"> Hz
  </p>
  <p>
    Target Duty Cycle: <input type="number" name="targetDuty" value="%TARGETDUTY%"> %
  </p>
    <input type="submit" value="설정변경">
  </form>
</body>
</html>
)rawliteral";

String processor(const String& var) {
  if (var == "FREQUENCY") {
    return String(pwmFreq);
  } else if (var == "TARGETDUTY") {
    return String(targetDuty);
  }
  return String();
}

void setupWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage1;
    String inputMessage2;

    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      pwmFreq = inputMessage1.toInt();
    }

    if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      targetDuty = inputMessage2.toFloat();
    }

    // PWM 설정을 다시 적용
    ledcDetach(pwmPin);
    delay(10);
    ledcAttach(pwmPin, pwmFreq, pwmResolution);
    if (pwmRunning) {
      softStart();
    }

    request->send(200, "text/html", "Settings updated!<br><a href=\"/\">Return to home</a>");
  });

  server.begin();
}