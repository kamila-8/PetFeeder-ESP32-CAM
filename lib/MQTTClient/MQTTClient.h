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

    void connect();


    void loop();

    void publish(const char* topic, const char* message);

    bool publish(const char* topic, const uint8_t* payload, size_t length);

    void subscribe(const char* topic);

    bool isConnected();

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




