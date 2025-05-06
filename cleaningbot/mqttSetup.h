// mqttSetup.h
#include <PubSubClient.h>
#include <ArduinoJson.h>


// 접속할 MQTT 주소
const char* mqttName = "cleaningbot_01";
const char* mqttTopic = "cleaningbot_in";
const char* mqttServer = "192.168.0.5";;
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient); // MQTT프로토콜 클래스


bool cleaningbotRuningState = false;


void setMQTT();
void reconnectMQTT();
void sendWeightMQTT();
void sendMqttJson();
void sendMqttError(String errorMessage);


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
  const char* robotName = doc["robotname"]; // 문자열로 추출
  bool robotState = doc["robotstate"];
  if (strcmp(robotName, mqttName) == 0) {
    if (robotState == false){
      cleaningbotRuningState = false;
      Serial.println("청소봇 청소 종료");
    }else if(robotState == true){
      if(cleaningbotRuningState == true){
        sendMqttError("해당 로봇이 이미 청소중입니다.");
      }else{
        cleaningbotRuningState = true;
        Serial.println("청소봇 청소 시작");
      }
    }
  }
}

void setMQTT(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect(mqttName)) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(mqttTopic);
    }
    else {
      Serial.println("Connection to MQTT Broker failed...");
      delay(1000);
    }
  }
}

void reconnectMQTT() {
  // 클라이언트가 연결되지 않은 경우 재연결을 시도
  while (!client.connected()) {
    Serial.print("MQTT 서버에 연결 시도...");
    // MQTT 서버에 연결을 시도합니다.
    if (client.connect(mqttName)) {
      Serial.println("MQTT 서버에 연결되었습니다!");
      // 여기서 구독 재설정을 수행할 수 있습니다.
      client.subscribe(mqttTopic);
    } else {
      Serial.print("연결 실패, rc=");
      Serial.print(client.state());
      Serial.println(" 다시 시도...");
      delay(3000);
    }
  }
}


void sendMqttJson(bool state){
  StaticJsonDocument<200> doc;
  // JSON 오브젝트에 cleaningbotState 값을 추가
  doc["robotName"] = mqttName;
  doc["robotState"] = state;
  // JSON 형식의 문자열로 변환
  char json[200];
  serializeJson(doc, json);
  // MQTT 브로커에 데이터 전송
  client.publish("mainServer", json);
}

void sendMqttError(String errormessage){
  StaticJsonDocument<200> doc;
  // JSON 오브젝트에 cleaningbotState 값을 추가
  doc["robotName"] = mqttName;
  doc["robotError"] = errormessage;
  // JSON 형식의 문자열로 변환
  char json[200];
  serializeJson(doc, json);
  // MQTT 브로커에 데이터 전송
  client.publish("mainserver", json);
}