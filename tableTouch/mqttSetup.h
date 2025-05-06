// mqttSetup.h
#include <PubSubClient.h>
#include <ArduinoJson.h>

// 테이블 번호
int tableNumber = 1;
// 접속할 MQTT명
const char* subcribeMqttTopicName = "tableButton";
// 로봇
bool cleaningRobotState = false;

// 접속할 MQTT 주소
const char* mqttServer = "192.168.0.137";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient); // MQTT프로토콜 클래스

void reconnectMQTT();
void sendMqttJson();


// 구독중인 "tableButton 토픽으로
// var message = {
//     tableNumber: 1,
//     cleaningRobotState: true
// }
// client.publish('tableButton', JSON.stringify(message));

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

  int incomingTableNumber = doc["tableNumber"]; // 들어오는 tableNumber 값 추출
  bool incomingCleaningRobotState = doc["cleaningRobotState"]; // 들어오는 cleaningRobotState 값 추출
  if (incomingTableNumber == tableNumber) {
    // 일치한다면 cleaningRobotState 값을 들어온 값으로 업데이트
    if (!incomingCleaningRobotState) { // incomingCleaningRobotState가 false일 경우만
        cleaningRobotState = false; // cleaningRobotState를 false로 업데이트
    }
    Serial.print("Table number ");
    Serial.print(tableNumber);
    Serial.print(" cleaning state updated to ");
    Serial.println(cleaningRobotState ? "true" : "false");
  }
}

void setMQTT(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(subcribeMqttTopicName);
    }
    else {
      Serial.println("Connection to MQTT Broker failed...");
      delay(100);
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
      client.subscribe(subcribeMqttTopicName); // "table" 토픽 구독
    } else {
      Serial.print("MQTT 서버 연결 실패, rc=");
      Serial.print(client.state());
      Serial.println(" 다시 시도합니다...");
      // 연결 시도 사이에 짧은 지연을 둡니다.
      delay(100);
    }
  }
}

void sendMqttJson(bool call){
    StaticJsonDocument<200> doc;
    // JSON 오브젝트에 cleaningRobotState 값을 추가
    doc["cleaningRobotState"] = call;
    doc["tableNumber"] = tableNumber;
    // JSON 형식의 문자열로 변환
    char json[200];
    serializeJson(doc, json);
    // MQTT 브로커에 데이터 전송
    client.publish("mainServer", json);
}


