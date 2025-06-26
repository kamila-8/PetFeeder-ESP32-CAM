#include "CameraManager.h"
#include "esp_camera.h"

// Constructor: link to MQTT client
CameraManager::CameraManager(MQTTClient& mqttClient) : mqtt(mqttClient), isInitialized(false) {
}

// Initialize the ESP32-CAM with pin mapping and settings
void CameraManager::init() {
    camera_config_t config;

    // Pin configuration (specific to AI Thinker ESP32-CAM)
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = 5;
    config.pin_d1 = 18;
    config.pin_d2 = 19;
    config.pin_d3 = 21;
    config.pin_d4 = 36;
    config.pin_d5 = 39;
    config.pin_d6 = 34;
    config.pin_d7 = 35;
    config.pin_xclk = 0;
    config.pin_pclk = 22;
    config.pin_vsync = 25;
    config.pin_href = 23;
    config.pin_sccb_sda = 26;
    config.pin_sccb_scl = 27;
    config.pin_pwdn = 32;
    config.pin_reset = -1;

    // Camera parameters
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // Initialize camera hardware
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x\n", err);
        isInitialized = false;
        return;
    }

    isInitialized = true;
    Serial.println("Camera initialized successfully");
}



