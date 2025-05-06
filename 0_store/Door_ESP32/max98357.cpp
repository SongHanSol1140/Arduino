
#include "max98357.h"
#include "variables.h"

// 전역 변수 정의
TaskHandle_t audioTaskHandle = NULL;
char currentAudioFile[64];
// I2S 초기화
void initI2S(uint32_t sampleRate, uint16_t bitsPerSample, uint16_t numChannels) {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = sampleRate,
    .bits_per_sample = bitsPerSample == 16 ? I2S_BITS_PER_SAMPLE_16BIT : I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = numChannels == 1 ? I2S_CHANNEL_FMT_ONLY_RIGHT : I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 16,
    .dma_buf_len = 128,
    .use_apll = true,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK_PIN,
    .ws_io_num = I2S_LRCLK_PIN,
    .data_out_num = I2S_DATA_PIN,
    .data_in_num = GPIO_NUM_NC
  };

  // 기존 드라이버 제거 (필요한 경우)
  i2s_driver_uninstall(I2S_NUM_0);

  // 드라이버 설치
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}



bool readWAVHeader(File &file, WAVHeader &header) {
  file.seek(22);
  if (file.read((uint8_t *)&header.numChannels, sizeof(header.numChannels)) != sizeof(header.numChannels))
    return false;

  if (file.read((uint8_t *)&header.sampleRate, sizeof(header.sampleRate)) != sizeof(header.sampleRate))
    return false;

  file.seek(34);
  if (file.read((uint8_t *)&header.bitsPerSample, sizeof(header.bitsPerSample)) != sizeof(header.bitsPerSample))
    return false;

  file.seek(44);
  return true;
}


void playWav(const char *fileName) {
  String filePath = "/" + String(fileName);
  // String filePath = "/" + String(fileName) + ".wav";

  // Open file
  File file = SD.open(filePath);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Read WAV header
  WAVHeader header;
  if (!readWAVHeader(file, header)) {
    Serial.println("Failed to read WAV header");
    return;
  }

  // // Setup I2S
  // i2s_config_t i2s_config = {
  //   .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
  //   .sample_rate = header.sampleRate,
  //   .bits_per_sample = header.bitsPerSample == 16 ? I2S_BITS_PER_SAMPLE_16BIT : I2S_BITS_PER_SAMPLE_32BIT,
  //   .channel_format = header.numChannels == 1 ? I2S_CHANNEL_FMT_ONLY_RIGHT : I2S_CHANNEL_FMT_RIGHT_LEFT,
  //   .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
  //   .intr_alloc_flags = 0,
  //   .dma_buf_count = 16,  // 기존 8에서 16으로 증가
  //   .dma_buf_len = 128,   // 기존 64에서 128로 증가
  //   .use_apll = true, //apll 사용
  //   .tx_desc_auto_clear = true,
  //   .fixed_mclk = 0
  // };

  // i2s_pin_config_t pin_config = {
  //   .bck_io_num = I2S_BCLK_PIN,
  //   .ws_io_num = I2S_LRCLK_PIN,
  //   .data_out_num = I2S_DATA_PIN,
  //   .data_in_num = GPIO_NUM_NC
  // };

  // i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  // i2s_set_pin(I2S_NUM_0, &pin_config);
  // i2s_set_clk(I2S_NUM_0, header.sampleRate, (i2s_bits_per_sample_t)header.bitsPerSample, (i2s_channel_t)header.numChannels);

  // Buffer for data
  uint8_t *buffer = (uint8_t *)malloc(READ_BUF_LEN);

  // Read data and write to I2S
  while (file.available()) {
    int read = file.read(buffer, READ_BUF_LEN);
    if (read > 0) {
      size_t written = 0;
      i2s_write(I2S_NUM_0, buffer, read, &written, portMAX_DELAY);
    }
  }

  // Close file
  file.close();

  // Free buffer
  free(buffer);

  // Uninstall I2S driver after playing sound
  i2s_driver_uninstall(I2S_NUM_0);
}










// ======================================================================

// 재생용 태스크 함수
static void playWavTask(void *param) {
  const char *fileName = (const char *)param;
  audioPlay = true;   // 재생 시작 플래그
  playWav(fileName);  // 블로킹 WAV 재생
  audioPlay = false;  // 재생 종료 플래그
  free(param);        // strdup으로 할당한 메모리 해제
  vTaskDelete(NULL);  // 태스크 종료
}

void playWavNonBlocking(const char *fileName) {
  if (audioPlay) {
    Serial.println("이미 재생 중입니다.");  // “Already playing.”
    return;
  }
  Serial.println("오디오 재생시작");
  // 파일명 문자열을 태스크에 넘기기 위해 strdup
  char *nameCopy = strdup(fileName);

  if (!nameCopy) {
    Serial.println("메모리 할당 실패");  // Memory allocation failed
    return;
  }
  // 태스크 생성: 스택 크기 8192바이트, 우선순위 1, 코어 0
  BaseType_t ret = xTaskCreatePinnedToCore(
    playWavTask,
    "playWavTask",
    8192,
    nameCopy,
    1,
    NULL,
    0);
  if (ret != pdPASS) {
    Serial.println("태스크 생성 실패");  // Task creation failed
    free(nameCopy);
  }
}