#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <driver/i2s.h>
#include <ArduinoJson.h>
#include "config.h"

WebSocketsClient webSocket;
bool isConnected = false;

void init_i2s_mic() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false
    };
    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_MIC_SCK,
        .ws_io_num = I2S_MIC_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = I2S_MIC_SD
    };
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
}

void init_i2s_speaker() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false
    };
    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SPEAKER_BCLK,
        .ws_io_num = I2S_SPEAKER_LRC,
        .data_out_num = I2S_SPEAKER_DIN,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_1, &pin_config);
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            isConnected = false;
            break;
        case WStype_CONNECTED:
            isConnected = true;
            char authPayload[128];
            snprintf(authPayload, sizeof(authPayload), "{\"type\":\"auth\",\"device_id\":\"%s\"}", XIAOZHI_DEVICE_ID);
            webSocket.sendTXT(authPayload);
            break;
        case WStype_TEXT:
            break;
        case WStype_BIN:
            size_t bytes_written;
            i2s_write(I2S_NUM_1, payload, length, &bytes_written, portMAX_DELAY);
            break;
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) { delay(500); }
    init_i2s_mic();
    init_i2s_speaker();
    webSocket.beginSSL(XIAOZHI_SERVER, XIAOZHI_PORT, "/v1/audio");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void loop() {
    webSocket.loop();
    if (isConnected) {
        uint8_t mic_buffer[512];
        size_t bytes_read;
        i2s_read(I2S_NUM_0, &mic_buffer, sizeof(mic_buffer), &bytes_read, portMAX_DELAY);
        if (bytes_read > 0) {
            webSocket.sendBIN(mic_buffer, bytes_read);
        }
    }
}
