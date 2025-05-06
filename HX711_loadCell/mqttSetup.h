// mqttSetup.h
#include <PubSubClient.h>
#include <ArduinoJson.h>

IPAddress ip(192, 168, 0, 233);// 고정접속할 IP - 사용중이지 않은 IP여야합니다.
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// 접속할 MQTT 주소
const char* mqttServer = "192.168.0.44";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient); // MQTT프로토콜 클래스

void setMQTT();
void reconnectMQTT();
void sendWeightMQTT();

typedef void (*SetZeroFactorFunc)(int); // 함수 포인터 타입 정의
SetZeroFactorFunc setZeroFactorFunc; // 함수 포인터 선언

void setZeroFactorCallback(SetZeroFactorFunc func) {
  setZeroFactorFunc = func; // 함수 포인터 설정
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  char msg[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    msg[i] = (char)payload[i];
  }
  msg[length] = '\0';
  // Serial.println(msg);

  // JSON 메시지 파싱
  StaticJsonDocument<200> doc;
  deserializeJson(doc, msg);
  const char* command = doc["command"];

  // "setZeroFactor" 커맨드 확인
  if (strcmp(command, "setZeroFactor") == 0) {
    // setZeroFactor();
    // 함수 포인터를 통해 setZeroFactor 함수 호출
    if (setZeroFactorFunc != NULL) {
      setZeroFactorFunc(20); // repeatNumber를 원하는 값으로 설정하세요.
    }
  }
}

void setMQTT(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect("loadCell_MQTT")) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe("loadCell");

    }
    else {
      Serial.println("Connection to MQTT Broker failed...");
      delay(1000);
    }
  }
}

void reconnectMQTT() {
  // MQTT 서버에 연결되어 있지 않다면
  if (!client.connected()) {
    Serial.println("MQTT 서버에 연결되어 있지 않습니다. 연결을 시도합니다...");
    
    // 클라이언트 ID를 무작위로 생성
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // MQTT 서버에 연결 시도
    if (client.connect(clientId.c_str())) {
      Serial.println("MQTT 서버에 연결되었습니다.");
      // 여기에 구독 코드 추가 (필요한 경우)
      client.subscribe("loadCell"); // "loadCell" 토픽 구독
    } else {
      Serial.print("MQTT 서버 연결 실패, rc=");
      Serial.print(client.state());
      Serial.println(" 다시 시도합니다...");
      // 연결 시도 사이에 짧은 지연을 둡니다.
      delay(5000);
    }
  }
}

void sendWeightMQTT(float weightValue){
  // 측정한 무게값 MQTT Broker의 loadcell_out으로 전송
  StaticJsonDocument<100> doc;

  // JSON 오브젝트에 cleaningRobotState 값을 추가
  doc["model"] = "loadCell";
  doc["weight"] = weightValue;

  // JSON 형식의 문자열로 변환
  char json[100];
  serializeJson(doc, json);
  // MQTT 브로커에 데이터 전송
  client.publish("mainServer", json);
}


