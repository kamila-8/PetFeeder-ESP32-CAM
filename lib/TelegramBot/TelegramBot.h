#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "config.h"

class TelegramBot {
public:
    TelegramBot();                            // Constructor
    void begin();                             // Initialization 
    void sendPhoto(const uint8_t* image, size_t length);  // Sends JPEG image buffer to Telegram

private:
    WiFiClientSecure secureClient;            // Secure HTTPS connection
    UniversalTelegramBot* bot;                // Telegram Bot API handler
};

#endif

