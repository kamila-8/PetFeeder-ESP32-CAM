#include "MQTTClient.h"
#include <Arduino.h>

extern volatile bool feedRequested;
extern volatile bool photoRequested;

MQTTClient::MQTTClient() : client(wifiClient) {
}

// Configure broker address, port, credentials, and callback
void MQTTClient::begin(const char* broker, uint16_t port, const char* user, const char* password) {
    client.setServer(broker, port);
    mqttUser = user;
    mqttPassword = password;

    // Internal message handler using lambda
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->onMessage(topic, payload, length);
    });
}

// Reconnect loop (blocking) until connected to broker
void MQTTClient::connect() {
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect("PetFeederClient", mqttUser, mqttPassword)) {
            Serial.println("connected");
            client.subscribe("petfeeder/command");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retry in 5 seconds");
            delay(5000);
        }
    }
}

// Maintain connection and process messages
void MQTTClient::loop() {
    client.loop();
}

// Publish string message
void MQTTClient::publish(const char* topic, const char* message) {
    client.publish(topic, message);
}

// Publish binary payload (e.g. JPEG)
bool MQTTClient::publish(const char* topic, const uint8_t* payload, size_t length) {
    return client.publish(topic, payload, length);
}

// Subscribe to a topic
void MQTTClient::subscribe(const char* topic) {
    client.subscribe(topic);
}

// Check connection status
bool MQTTClient::isConnected() {
    return client.connected();
}

// Allow user to set external callback
void MQTTClient::setExternalCallback(MQTTCallback callback) {
    externalCallback = callback;
}

// Internal message handler, prints message and delegates to external callback
void MQTTClient::onMessage(char* topic, byte* payload, unsigned int length) {
    Serial.print("Received message on topic: ");
    Serial.println(topic);

    Serial.print("Message: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    if (externalCallback) {
        externalCallback(topic, payload, length);
    }
}








