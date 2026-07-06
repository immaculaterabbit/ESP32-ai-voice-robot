#ifndef CONFIG_H
#define CONFIG_H

// WiFi Credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

// Xiaozhi Dev Platform Settings
const char* XIAOZHI_SERVER = "api.xiaozhi.dev"; 
const int   XIAOZHI_PORT   = 443;
const char* XIAOZHI_DEVICE_ID = "YOUR_XIAOZHI_DEVICE_TOKEN";

// Audio Pin Configuration (Standard ESP32)
#define I2S_MIC_WS   25
#define I2S_MIC_SCK  26
#define I2S_MIC_SD   33

#define I2S_SPEAKER_LRC 22
#define I2S_SPEAKER_BCLK 19
#define I2S_SPEAKER_DIN 21

#endif
