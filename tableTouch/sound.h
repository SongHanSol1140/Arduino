// sound.h
#include <FS.h>
#include <SPIFFS.h>
#include "driver/i2s.h"

#define READ_BUF_LEN (64 * 1024)

// Pins for I2S
#define I2S_LRCLK_PIN 25
#define I2S_BCLK_PIN 26
#define I2S_DATA_PIN 27

void playWav();

struct WAVHeader{
    uint32_t sampleRate;
    uint16_t numChannels;
    uint16_t bitsPerSample;
};

bool readWAVHeader(File &file, WAVHeader &header){
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

void playWav(const char *fileName){
    String filePath = "/" + String(fileName) + ".wav";

    // Open file
    File file = SPIFFS.open(filePath);
    if (!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    // Read WAV header
    WAVHeader header;
    if (!readWAVHeader(file, header)){
        Serial.println("Failed to read WAV header");
        return;
    }

    // Setup I2S
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = header.sampleRate,
        .bits_per_sample = header.bitsPerSample == 16 ? I2S_BITS_PER_SAMPLE_16BIT : I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = header.numChannels == 1 ? I2S_CHANNEL_FMT_ONLY_RIGHT : I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0};

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK_PIN,
        .ws_io_num = I2S_LRCLK_PIN,
        .data_out_num = I2S_DATA_PIN,
        .data_in_num = I2S_PIN_NO_CHANGE};

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_set_clk(I2S_NUM_0, header.sampleRate, (i2s_bits_per_sample_t)header.bitsPerSample, (i2s_channel_t)header.numChannels);

    // Buffer for data
    uint8_t *buffer = (uint8_t *)malloc(READ_BUF_LEN);

    // Read data and write to I2S
    while (file.available()){
        int read = file.read(buffer, READ_BUF_LEN);
        if (read > 0)
        {
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
};