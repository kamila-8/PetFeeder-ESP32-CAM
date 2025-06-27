#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <esp_camera.h>
#include <Arduino.h>
#include "MQTTClient.h"

// Manages ESP32-CAM initialization and camera status
class CameraManager {
public:
    // Constructor: takes reference to MQTT client for integration
    CameraManager(MQTTClient& mqttClient);

    // Initialize the camera hardware
    void init();

private:
    MQTTClient& mqtt;   
    bool isInitialized;  
};

#endif












