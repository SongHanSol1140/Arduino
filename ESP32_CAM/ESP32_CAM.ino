// ESP32_CAM.ino
// Board
// AI Thinker ESP32-CAM
#include "esp_camera.h"
#include <WiFi.h>


#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// WiFi 설정
const char *ssid = "NNX2-2.4G";
const char *password = "$@43skshslrtm";
const IPAddress local_IP(192, 168, 0, 8); // 고정 IP 주소
const IPAddress gateway(192, 168, 0, 1); // 게이트웨이 주소
const IPAddress subnet(255, 255, 255, 0); // 서브넷 마스크
void startCameraServer();
void setupLedFlash(int pin);

void setWIFI() {
  // 고정 IP 설정
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);
    int max_retries = 20;  // 최대 재시도 횟수
    int retries = 0;

    // Wi-Fi가 연결될 때까지 대기 (최대 재시도 횟수 만큼)
    while (WiFi.status() != WL_CONNECTED && retries < max_retries) {
      delay(500);
      Serial.print(".");
      retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");

      Serial.print("Camera Ready! Use 'http://");
      Serial.print(WiFi.localIP());
      Serial.println("' to connect");
    } else {
      Serial.println("");
      Serial.println("WiFi connection failed");
    }
  }
}

void setup() {
  Serial.begin(115200);
  // Serial.begin(250000);
  Serial.setDebugOutput(true);
  Serial.println("Setup starting...");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 30000000; // 기본클럭
  // config.xclk_freq_hz = 10000000;
  // 기본해상도 설정
  config.frame_size = FRAMESIZE_HVGA;
  // config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 32;
  config.fb_count = 1;

  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 32;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // 기본설정
      config.frame_size = FRAMESIZE_HVGA;
      // config.frame_size = FRAMESIZE_HVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // 기본설정
    config.frame_size = FRAMESIZE_HVGA;
    // config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

  // 카메라 초기화 이전에 GPIO 32를 HIGH로 설정
  pinMode(PWDN_GPIO_NUM, OUTPUT);
  digitalWrite(PWDN_GPIO_NUM, HIGH);

  Serial.println("Initializing camera...");
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    return;
  }
  Serial.println("Camera initialized");

  sensor_t *s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);
    s->set_brightness(s, 1);
    s->set_saturation(s, -2);
  }
  if (config.pixel_format == PIXFORMAT_JPEG) {
    // 기본 해상도 설정
    // s->set_framesize(s, FRAMESIZE_HVGA);
    s->set_framesize(s, FRAMESIZE_HVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

#if defined(LED_GPIO_NUM)
  setupLedFlash(LED_GPIO_NUM);
#endif

  // WiFi 연결 시도
  Serial.println("Connecting to WiFi...");
  setWIFI();

  Serial.println("Starting camera server...");
  startCameraServer();
  Serial.println("Setup complete");
}

void loop() {
  setWIFI();  // 필요 시 WiFi 재연결 시도
  delay(10000);
}
