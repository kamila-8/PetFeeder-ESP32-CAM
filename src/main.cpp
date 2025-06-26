#include <WiFi.h>
#include "config.h"
#include "MQTTClient.h"
#include "ServoController.h"
#include "CameraManager.h"
#include "TelegramBot.h"

MQTTClient mqtt;
ServoController servo(14);
CameraManager camera(mqtt);
TelegramBot telegram;

volatile bool feedRequested = false;
volatile bool photoRequested = false;
bool manualTriggered = false;


unsigned long lastAutoFeedTime = 0;
const unsigned long autoFeedInterval = 5 * 60 * 1000;

const int feedButtonPin = 13;


void feed(const String& source) {
    Serial.print("Feeding... Source: ");
    Serial.println(source);

    servo.open();
    servo.close();

    if (source == "auto") {
        mqtt.publish("petfeeder/status", "Auto Fed");
        Serial.println("Auto Fed");
    } else if (source == "manual") {
        mqtt.publish("petfeeder/status", "Manual Fed");
        Serial.println("Manual Fed");
    } else {
        mqtt.publish("petfeeder/status", "Fed");
        Serial.println("Fed");
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 STARTED");

    pinMode(feedButtonPin, INPUT_PULLUP);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

   
    mqtt.begin(MQTT_BROKER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD);
    mqtt.setExternalCallback(onMessage);
    mqtt.connect();
    mqtt.subscribe("petfeeder/command");

    camera.init();
    telegram.begin();

    lastAutoFeedTime = millis();
}

void loop() {
    mqtt.loop();

    unsigned long currentTime = millis();

    
    if (digitalRead(feedButtonPin) == LOW) {
        manualTriggered = true;
        feedRequested = true;
        delay(500);
    }
    
    if ((currentTime - lastAutoFeedTime) >= autoFeedInterval) {
        lastAutoFeedTime = currentTime;
        feed("auto");
    }

    if (feedRequested) {
        feedRequested = false;

        if (manualTriggered) {
            feed("manual");
            manualTriggered = false;
        } else {
            feed("mqtt");
        }
    }

    if (photoRequested) {
        photoRequested = false;
        sendPhoto();
    }
}

