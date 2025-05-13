/*
    Hans Robot Gripper 이슈

    => 나노닉스에서 별도로 모터를 이용해 만든 그리퍼임

    모터가 동작을 안하는 문제 (MQTT를 ESP32가 분명히 받지만 동작을 안했었음)					
        => 배선을 잘못함				
        => 코드에서 '2'핀은 D2가 아님, 2번핀을 D2로 설정해놔서 그리퍼가 동작하지 않았던것		

    USB 사용안할시 작동을 안하는문제(ESP32C3이 부팅이 안되는 경우)					
        => 상민 씨 코드에서 while(!Serial)부분이 문제였음				
        => Serial은 USB가 연결되어 시리얼인터페이스가 활성화되어야 리턴됨				
    모터 현재위치 확인					
        Serial.println(driver.XACTUAL());				
        driver.XACTUAL() => 모터 현재 포지션값 확인				
        우리가 position 20000으로 보낼시 도착후 측정해보면 20000이 나옴				
					
    이외 각종에러 출력방법 driver.DRV_STATUS()					
        driver.DRV_STATUS()를 사용하면 될거라고 판단되는데				
        0101010101111010101011와 같이 비트로 데이터가 들어오기 때문에 추후 tmc5160 메뉴얼을 찾아서 확인해볼것			
*/



#include <TMCStepper.h>
#include <WiFi.h>
#include <MQTT.h>
#include <iostream>
#include <typeinfo>



#define EN_PIN 3    // Enable D3
#define CS_PIN 2    // Chip select D2
#define SW_MOSI 10  // Software Master Out Slave In (MOSI) D10
#define SW_MISO 9   // Software Master In Slave Out (MISO) D9
#define SW_SCK 8    // Software Slave Clock (SCK)

const char ssid[] = "경영지원 2 2.4G";   //Wifi 이름
const char pass[] = "$@43skshslrtm";     //Wifi 비밀번호
IPAddress address(192, 168, 0, 19);      //MQTT Broker IP
const char topic[] = "gripper";          //명령 들어오는 topic
const char send_topic[] = "controller";  //상태 내보내는 topic

int origin = 0;            //원점 위치
int position1 = -40000;    //1번 위치
int position2 = 20000;     //2번 위치
int position3 = 30000;     //3번 위치
int position4 = 40000;     //4번 위치
int position5 = 50000;     //5번 위치
int position6 = 60000;     //6번 위치
int position7 = 70000;     //7번 위치
int position8 = 80000;     //8번 위치
int position9 = 90000;     //9번 위치
int position10 = 2000000;  //10번 위치

/////////////Settings
//Current Settings
int GLOBALSCALER = 200;  // GLOBALSCALER    (0 ~ 255)
int IHOLDDELAY = 1;      // IHOLDDELAY      (1 ~ 15)
int IRUN = 2;            // IRUN            (0 ~ 31)
int IHOLD = 1;           // IHOLD           (0 ~ 31)

//Accleration settings
int VSTART = 2000;  // VSTART        (0 ~ 262143)
int A1_ = 1000;     // A1            (0 ~ 65535)
int V1 = 40000;     // V1            (0 ~ 1048575)
int AMAX = 500;     // AMAX          (0 ~ 8388096)
int VMAX = 50000;   // VMAX          (0 ~ 8388095)
int DMAX = 500;     // DMAX          (0 ~ 66535)
int D1_ = 1000;     // D1            (0 ~ 65535)
int VSTOP = 10000;  // VSTOP         (0 ~ 262143)

//COOLCONFIG
bool sfilt = true;   // sfilt        (true, false)
int sgt = 10;        // sgt          (-64 ~ 63)
int seimin = false;  // seimin       (true, false)
int sedn = 2;        // sedn         (0 ~ 3)
int semax = 5;       // semax        (0 ~ 15)
int seup = 2;        // seup         (0 ~ 3)
int semin = 0;       // semin        (0 ~ 15)

//TSTEP threshold
int TPWMTHRS = 650;   // TOWMTHRS     (0 ~ 1048575)
int TCOOLTHRS = 34;   // TCOOLTHRS    (0 ~ 1048575)
int THIGH = 33;       // TCOOLTHRS    (0 ~ 1048575)
int VDCMIN = 500000;  // VDCMIN       (256 ~ 1048575)

//SWMODE
bool en_softstop = false;  // en_softstop  (true, false)
bool sg_stop = true;       // sg_stop      (true, false)

//DC Ctrl
int DC_TIME = 0;  // DC_TIME      (0 ~ 1023)
int DC_SG = 0;    // DC_SG        (0 ~ 255)

//PWMCONF
int pwm_lim = 12;           // pwm_lim      (0 ~ 15)
int pwm_reg = 4;            // pwm_reg      (0 ~ 15)
bool pwm_autograd = true;   // pwm_autograd (true, false)
bool pwm_autoscale = true;  // pwm_autoscale(true, false)
int pwm_freq = 2;           // pwm_freq     (0 ~ 3)
int pwm_GRAD = 31;          // pwm_GRAD     (0 ~ 255)
int pwm_OFS = 255;          // pwm_OFS      (0 ~ 255)

//CHOPCONF
bool vhighchm = true;       // vhighchm       (true, false)
bool vhighfs = true;        // vhighfs        (true, false)
int tbl = 2;                // tbl            (0 ~ 3)
bool chopper_mode = false;  // chopper mode   (true, false)
bool disfdcc = false;       // disfdcc        (true, false)
bool fd3 = false;           // fd3            (true, false)
int hend = 1;               // hend           (-3 ~ 12)
int hstrt = 4;              // hstrt          (0 ~ 15)
int toff = 8;               // toff           (0 ~ 15)

//GCONF
bool multistep_filt = true;  // multistep filter   (true, false)
bool en_pwm_mode = true;     // en pwm mode        (true, false)
int TPOWERDOWN = 10;         // tpowerdown         (10 ~ 255)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define R_SENSE 0.11f  // Match to your driver

TMC5160Stepper driver = TMC5160Stepper(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

WiFiClient net;
MQTTClient client;



void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("gripper", "gripper", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

String Split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void default_settings() {
  driver.GLOBAL_SCALER(GLOBALSCALER);
  driver.iholddelay(IHOLDDELAY);
  driver.irun(IRUN);
  driver.ihold(IHOLD);

  driver.VSTART(VSTART);
  driver.a1(A1_);
  driver.v1(V1);
  driver.AMAX(AMAX);
  driver.VMAX(VMAX);
  driver.DMAX(DMAX);
  driver.d1(D1_);
  driver.VSTOP(VSTOP);

  driver.sfilt(sfilt);
  driver.sgt(sgt);
  driver.seimin(seimin);
  driver.sedn(sedn);
  driver.semax(semax);
  driver.seup(seup);
  driver.semin(semin);

  driver.TPWMTHRS(TPWMTHRS);
  driver.TCOOLTHRS(TCOOLTHRS);
  driver.THIGH(THIGH);
  driver.VDCMIN(VDCMIN);

  driver.en_softstop(en_softstop);
  driver.sg_stop(sg_stop);

  driver.dc_time(DC_TIME);
  driver.dc_sg(DC_SG);

  driver.pwm_lim(pwm_lim);
  driver.pwm_reg(pwm_reg);
  driver.pwm_autograd(pwm_autograd);
  driver.pwm_autoscale(pwm_autoscale);
  driver.pwm_freq(pwm_freq);
  driver.pwm_grad(pwm_GRAD);
  driver.pwm_ofs(pwm_OFS);


  driver.vhighchm(vhighchm);
  driver.vhighfs(vhighfs);
  driver.tbl(tbl);
  driver.chm(chopper_mode);
  driver.disfdcc(disfdcc);
  driver.hend(hend);
  driver.hstrt(hstrt);
  driver.toff(toff);

  driver.multistep_filt(multistep_filt);
  driver.en_pwm_mode(en_pwm_mode);
  driver.TPOWERDOWN(TPOWERDOWN);
  driver.event_stop_sg();

  Serial.print("DRV_STATUS=0b");
  Serial.println(driver.DRV_STATUS(), BIN);
  Serial.println(driver.DRV_STATUS());
  driver.RAMPMODE(0);
  driver.XACTUAL(0);
  driver.XTARGET(0);
}

void go_to(int position) {
  driver.RAMPMODE(0);
  driver.VMAX(150000);
  driver.XTARGET(position);
}
void velocity(bool dir, int speed) {
  if (dir) {
    driver.RAMPMODE(1);
    driver.VMAX(speed);
  } else {
    driver.RAMPMODE(2);
    driver.VMAX(speed);
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);


  String first = Split(payload, '/', 0);
  String second = Split(payload, '/', 1);

  if (first == "home") {
    Serial.println("home");
    client.publish(send_topic, "home");

    go_to(origin);
  } else if (first == "pos1") {
    Serial.println("pos1");
    client.publish(send_topic, "pos1");

    go_to(position1);
  } else if (first == "pos2") {
    client.publish(send_topic, "pos2");
    Serial.println("pos2");
    go_to(position2);
  } else if (first == "pos3") {
    Serial.println("pos3");
    client.publish(send_topic, "pos3");
    go_to(position3);
  } else if (first == "pos4") {
    Serial.println("pos4");
    client.publish(send_topic, "pos4");
    go_to(position4);
  } else if (first == "pos5") {
    Serial.println("pos5");
    client.publish(send_topic, "pos5");
    go_to(position5);
  } else if (first == "pos6") {
    Serial.println("pos6");
    client.publish(send_topic, "pos6");
    go_to(position6);
  } else if (first == "pos7") {
    Serial.println("pos7");
    client.publish(send_topic, "pos7");
    go_to(position7);
  } else if (first == "pos8") {
    Serial.println("pos8");
    client.publish(send_topic, "pos8");
    go_to(position8);

  } else if (first == "pos9") {
    Serial.println("pos9");
    client.publish(send_topic, "pos9");
    (position9);
  } else if (first == "pos10") {
    Serial.println("pos10");
    go_to(position10);
  } else if (first == "move") {
    Serial.print("move to : ");
    Serial.println(second);
    go_to(second.toInt());
  } else if (first == "left") {
    velocity(0, second.toInt());
  } else if (first == "right") {
    velocity(1, second.toInt());
  } else if (first == "stop") {
    velocity(0, 0);
  } else if (first == "position") {
    Serial.print("Position : ");
    int a = driver.XACTUAL();
    Serial.println(a);
    client.publish(send_topic, "position/" + String(a));
  } else if (first == "target") {
    Serial.print("Target : ");
    Serial.println(driver.XTARGET());
  } else if (first == "sethome") {
    driver.RAMPMODE(0);
    driver.XACTUAL(0);
    driver.XTARGET(0);
  } else if (first == "stall") {
    //stall detect
  } else if (first == "resetStall") {
    // reset stall
  }
}
void setup() {

  Serial.begin(9600);
  // while(!Serial);

  Serial.println("Start...");
  driver.begin();  // Initiate pins and registeries
  default_settings();

  // digitalWrite(EN_PIN, HIGH);

  WiFi.begin(ssid, pass);

  client.begin(address, net);
  client.onMessage(messageReceived);
  connect();

  client.subscribe(topic);
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  // 현재 모터 위치값 받기 (position값)
  Serial.println(driver.XACTUAL()); 
  
  delay(100);
}
