#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

// Define callback type for handling incoming MQTT messages
typedef void (*MQTTCallback)(char* topic, byte* payload, unsigned int length);

// Simple wrapper around PubSubClient for MQTT communication
class MQTTClient {
public:
    MQTTClient();  // Constructor

    // Initialize MQTT client with broker address and credentials
    void begin(const char* broker, uint16_t port, const char* user, const char* password);

    // Connect to the broker (retries until successful)
    void connect();

    // Must be called in loop() to maintain MQTT connection and receive messages
    void loop();

    // Publish plain text message
    void publish(const char* topic, const char* message);

    // Publish binary data (e.g. images)
    bool publish(const char* topic, const uint8_t* payload, size_t length);

    // Subscribe to a topic
    void subscribe(const char* topic);

    // Check if currently connected to broker
    bool isConnected();

    // Set user-defined callback to handle incoming messages
    void setExternalCallback(MQTTCallback callback);

private:
    WiFiClient wifiClient;
    PubSubClient client;

    const char* mqttUser;
    const char* mqttPassword;

    MQTTCallback externalCallback = nullptr;

    // Internal handler for MQTT messages, forwards to externalCallback
    void onMessage(char* topic, byte* payload, unsigned int length);
};

#endif




