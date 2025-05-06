// 수정
// 100/50 안깜박거림
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <SoftwareSerial.h>
///////////////////////////////////////////////////////////////////////////////
//버튼 핀번호
#define bean 7 //원두
#define set_double 8 //2배
#define espresso  9// 작은 에스프레소
#define espresso_long  6 // 큰 에스프레소
#define coffee 10 //작은 커피
#define coffee_long  5// 큰 커피
#define steam  11 // 취소
#define clean   4 // 세척

#define BeanErrorCleared 12
SoftwareSerial SoftSerial(3, 2); // Rx, Tx

//와이파이 세팅
const char ssid[] = "NNX2-2.4G";        //Wifi 이름 
// const char ssid[] = "nnx-factory5";        //Wifi 이름 
const char pass[] = "$@43skshslrtm";    //Wifi 비밀번호
int status = WL_IDLE_STATUS;     // the WiFi radio's status

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//MQTT 세팅
const char broker[] = "192.168.0.44";
int        port     = 1883;
const char topic[]  = "coffee";     // 기기명(기계별로 각자 달라야 함)
const char send_topic[] = "coffee_controller"; //서버 명

//const long interval = 1000;
//unsigned long previousMillis = 0;
const int MAX_NUM = 8;
int order[MAX_NUM]; // 0 = 
int order_pos = 0;
int plus_num = 0;
int absol_pos = 0;
char data;
bool isNoBean = false;
int delaytime = 5000;
int btnRestTime = 3000;
int lastOrder = 0;

volatile unsigned long nowTime;
volatile unsigned long preTime;
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  SoftSerial.begin(9600, SERIAL_8N1);
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.print("You're connected to the network");
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(topic);



  // PWM 출력 설정
  pinMode(bean, OUTPUT);
  pinMode(set_double, OUTPUT);
  pinMode(espresso, OUTPUT);
  pinMode(espresso_long, OUTPUT);
  pinMode(coffee, OUTPUT);
  pinMode(coffee_long, OUTPUT);
  pinMode(steam, OUTPUT);
  pinMode(clean, OUTPUT);
  
  digitalWrite(bean, 0);
  digitalWrite(set_double, 0);
  digitalWrite(espresso, 0);
  digitalWrite(espresso_long, 0);
  digitalWrite(coffee, 0);
  digitalWrite(coffee_long, 0);
  digitalWrite(steam, 0);
  digitalWrite(clean, 0);

  pinMode(BeanErrorCleared, INPUT_PULLUP);
}

void loop() {

  nowTime = millis();
  
  mqttClient.poll();
  if(!digitalRead(BeanErrorCleared)){
    Serial.println("Bean error CLEARED!!");
    sendMessage("bean/cleared");
    isNoBean = false;
  }
  delay(1000);
  sendMessage("test");
  Serial.println("check");
  //if()// 원두 에러 초기화 버튼
  if(SoftSerial.available())
  {
    data = SoftSerial.read();
    //Serial.println(data,HEX);

    
    if(data == 0x10){ // normal
      sendMessage("Error/normal");
      // Serial.println(data, HEX);
      if(lastOrder !=0){
        switch(lastOrder){
          case 1: //원두

            break;
          case 2: //두배
            break;
          case 3: //에스프레소
            sendMessage("espresso/finished");
            Serial.println("espresso/finished");
            
            break;
          case 4: //에스프레소 롱고
            sendMessage("espressoLong/finished");
            Serial.println("espressoLong/finished");
            break;
          case 5: //커피
            sendMessage("coffee/finished");
            Serial.println("coffee/finished");
            break;
          case 6: //롱커피
            sendMessage("coffeeLong/finished");
            Serial.println("coffeeLong/finished");
            break;
          case 7: //스팀
            sendMessage("steam/finished");
            Serial.println("steam/finished");
            break;
          case 8: //세척
            sendMessage("clean/finished");
            Serial.println("clean/finished");
            break;
        }
        lastOrder = 0;
      }
    }
    else if(data == 0x11){ // power off
      sendMessage("Error/powerOff");
      Serial.println("Error/powerOff");
    }
    else if(data == 0x20){ // Operating
      // sendMessage("Error/operating");
      // Serial.println("Error/operating");
    }
    else if(data == 0x01){ // no water
      sendMessage("Error/noWater");
      Serial.println("Error/noWater");
    }
    else if(data == 0x02){ // water location
      sendMessage("Error/waterLocation");
      Serial.println("Error/waterLocation");
    }
    else if(data == 0x03){ //junk container full
      sendMessage("Error/junkContainerFull");
      Serial.println("Error/junkContainerFull");
    }
    else if(data == 0x04){ //junk container location
      sendMessage("Error/junkContainerLocation");
      Serial.println("Error/junkContainerLocation");
    }
    else if(data == 0x05){ //no beans
      isNoBean = true;
      sendMessage("Error/noBeans");
      Serial.println("Error/noBeans");
    }
    else if(data == 0x06){ //no ground beans
      sendMessage("Error/noGroundBeans");
      Serial.println("Error/noGroundBeans");
    }
    else if(data == 0x07){ //remove calcite
      sendMessage("Error/removeCalcite");
      Serial.println("Error/removeCalcite");
    
    }
    else if(data == 0x08){ //overgrounded
      sendMessage("Error/overGrounded");
      Serial.println("Error/overGrounded");
    }
    else if(data == 0x09){ //ground long coffee
      sendMessage("Error/groundLongCoffee");
      Serial.println("Error/groundLongCoffee");
    }
    else if(data == 0x0A){ //too much coffee
      sendMessage("Error/tooMuchCoffee");
      Serial.println("Error/tooMuchCoffee");
    }
    else if(data == 0x0B){ //empty pipe
      sendMessage("Error/emptyPipe");
      Serial.println("Error/emptyPipe");
    }
    else if(data == 0x0C){ //too dirty
      sendMessage("Error/tooDirty");
      Serial.println("Error/tooDirty");
    }
    else if(data == 0x0D){ //extractor location
      sendMessage("Error/extractorLocation");
      Serial.println("Error/extractorLocation");
    }
    else if(data == 0x0E){ //steam
      sendMessage("Error/steam");
      Serial.println("Error/steam");
    }
    else if(data == 0x0F){ //remove calcite 2
      sendMessage("Error/removeCalcite2");
      Serial.println("Error/removeCalcite2");
    }
    
  }

  if(nowTime - preTime >= 3000){
    if(order[order_pos] != 0 && data == 0x10 && isNoBean == false){
      switch(order[order_pos]){
        case 1:
          press_beanBtn();
          delay(btnRestTime);
          break;
        case 2:
          press_doubleBtn();
          delay(btnRestTime);
          break;
        case 3:
          press_espressoBtn();
          delay(btnRestTime);
          break;
        case 4:
          press_espressoLongBtn();
          delay(btnRestTime);
          break;
        case 5:
          press_coffeeBtn();
          delay(btnRestTime);
          break;
        case 6:
          press_coffeeLongBtn();
          delay(btnRestTime);
          break;
        case 7:
          press_steamBtn();
          delay(btnRestTime);
          break;
        case 8:
          press_cleanBtn();
          delay(btnRestTime);
          break;
      }
 
      order[order_pos] = 0;
      order_pos++;
      if(order_pos > 7){
        order_pos = 0;
      }
      plus_num--;
      Serial.print("deleted : ");
      for(int i = 0; i<8; i++){
        Serial.print(order[i]);
        Serial.print(" ");
      }
      /////
      data = 0x20;
      Serial.println("data changed to 0x20");
      preTime = nowTime;
    }
    else if(order[order_pos] != 0 && data == 0x10 && isNoBean == true){
      Serial.println("No Beans! fill it and push the button!");
    }
  }
  else{
    //Serial.println("resting");
  }

  delay(10);
}

String Split(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void sendMessage(String msg){
  mqttClient.beginMessage(send_topic);
  mqttClient.print(msg);
  mqttClient.endMessage();
}

void onMqttMessage(int messageSize) {
  String message = mqttClient.readString();
  Serial.println("incoming: " + mqttClient.messageTopic() + " - " + message);
  String first = Split(message,'/',0);
  String second = Split(message,'/',1 );
  if(first == "bean"){
    if(second == "clear"){
      Serial.println("Bean error CLEARED!!");
      sendMessage("bean/cleared");
      isNoBean = false;
    }
    else if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(1);
    }
    else if(second == "off"){
      Serial.println("bean off");
      // digitalWrite(bean,LOW);
    }
    
  }

  else if(first == "double"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(2);
    }
    else if(second == "off"){
      Serial.println("double off");
      //digitalWrite(set_double,LOW);
    }
  }

  else if(first == "espresso"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(3);
    }
    else if(second == "off"){
      Serial.println("espresso off");
      //digitalWrite(espresso,LOW);
    }
  }

  else if(first == "espressoLong"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(4);
    }
    else if(second == "off"){
      Serial.println("espresso long off");
      //digitalWrite(espresso_long,LOW);
    }
  }
  else if(first == "coffee"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(5);
    }
    else if(second == "off"){
      Serial.println("coffee off");
      //digitalWrite(coffee,LOW);
    }
  }
  else if(first == "coffeeLong"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(6);
    }
    else if(second == "off"){
      Serial.println("coffee long off");
      // digitalWrite(coffee_long,LOW);
    }
  }
  /////////////////////////////////////////////////////////조건 넣기
  else if(first == "steam"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(7);
    }
    else if(second == "off"){
      Serial.println("steam off");
      //digitalWrite(steam,LOW);
    }
  }
  else if(first == "esc"){
    Serial.println("");
    Serial.print("current Data : ");
    Serial.println(data,HEX);
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
         if(data != 0x10){
          press_steamBtn();
         }
         else{
          Serial.println("standby mode!");
         }
    }
    else if(second == "off"){
      Serial.println("esc off");
      //digitalWrite(steam,LOW);
    }
  }
  /////////////////////////////////////////////////////////
  else if(first == "clean"){
    if(isNoBean){
      sendMessage("bean/stillError");
      Serial.println("no beans! fill it and push the button!");
    }
    else if(second == "on"){
      add_order(8);
    }
    else if(second == "off"){
      Serial.println("clean off");
      //digitalWrite(clean,LOW);
    }
  }
  else if(first == "delay"){
    Serial.println("delay " + second);
    delaytime = second.toInt();
  }
  else{
    Serial.println("why why why why why");
  }
  delay(100);

}

void add_order(int i){
  if(plus_num < 8){
    if(order_pos + plus_num > MAX_NUM - 1){
    absol_pos = order_pos + plus_num - 8;
    }
    else{
      absol_pos = order_pos + plus_num;
    }
    order[absol_pos] = i;
    Serial.print("Add number  =  ");
    Serial.print(absol_pos);
    Serial.print("Added at = ");
    Serial.println(plus_num);
    plus_num ++;
    Serial.print("Added : ");
    for(int i = 0; i<8; i++){
      Serial.print(order[i]);
      Serial.print(" ");
    }
  }
  else {
    Serial.println();
    Serial.println(" OVERLOADED OVERLOADED!!");
    Serial.println();
  }
 
  /*
  for(int i = 0; i<8; i++){
      if(order_pos + i > 7){
        Serial.print(order[order_pos + i - 8]);
        Serial.print(" ");
      }
      else{
        Serial.print(order[order_pos + i]);
        Serial.print(" ");
      }
    }
    */
}



void press_beanBtn() {
  Serial.println("bean on");
  outputPWM(bean);
  sendMessage("bean/pressed");
  lastOrder = 1;
}

void press_doubleBtn() {
  Serial.println("double on");
  outputPWM(set_double);
  sendMessage("double/pressed");
  lastOrder = 2;
}

void press_espressoBtn() {
  Serial.println("espresso on");
  outputPWM(espresso);
  sendMessage("espresso/start");
  lastOrder = 3;
}

void press_espressoLongBtn() {
  Serial.println("espresso long on");
  outputPWM(espresso_long);
  sendMessage("espressoLong/start");
  lastOrder = 4;
}

void press_coffeeBtn() {
  Serial.println("coffee on");
  outputPWM(coffee);
  sendMessage("coffee/start");
  lastOrder = 5;
}

void press_coffeeLongBtn() {
  Serial.println("coffeeLong on");
  outputPWM(coffee_long);
  Serial.println("coffee long on");
  sendMessage("coffeeLong/start");
  lastOrder = 6;
}

void press_steamBtn() {
  Serial.println("steam on");
  outputPWM(steam);
  sendMessage("steam/start");
  lastOrder = 7;
}

void press_cleanBtn() {
  Serial.println("clean on");
  outputPWM(clean);
  sendMessage("clean/start");
  lastOrder = 8;
}

void outputPWM(int pin) {
  unsigned long endTime = millis() + delaytime;
  while (millis() < endTime) {
    digitalWrite(pin, HIGH);
    delay(2);  // 0.04초 ± 0.001초 동안 끄기
    digitalWrite(pin, LOW);
    delay(1);  // 0.02초 ± 0.002초 동안 끄기
  }
}