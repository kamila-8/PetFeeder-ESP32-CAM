#include "TelegramBot.h"
#include "config.h"

// Constructor: initialize secure client and Telegram bot
TelegramBot::TelegramBot() {
    secureClient.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    bot = new UniversalTelegramBot(TELEGRAM_BOT_TOKEN, secureClient);
}


void TelegramBot::begin() {
}

// Send photo to Telegram using multipart/form-data POST request
void TelegramBot::sendPhoto(const uint8_t* image, size_t length) {
    String boundary = "SFCAM";

    String start_request = "--" + boundary + "\r\n"
        "Content-Disposition: form-data; name=\"chat_id\"\r\n\r\n"
        + CHAT_ID + "\r\n--" + boundary + "\r\n"
        "Content-Disposition: form-data; name=\"photo\"; filename=\"cam.jpg\"\r\n"
        "Content-Type: image/jpeg\r\n\r\n";

    String end_request = "\r\n--" + boundary + "--\r\n";

    WiFiClientSecure client;
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

    if (!client.connect("api.telegram.org", 443)) {
        Serial.println("Telegram connection failed");
        return;
    }

    // Send HTTP headers
    client.print("POST /bot" + String(TELEGRAM_BOT_TOKEN) + "/sendPhoto HTTP/1.1\r\n");
    client.print("Host: api.telegram.org\r\n");
    client.print("Content-Type: multipart/form-data; boundary=" + boundary + "\r\n");
    client.print("Content-Length: " + String(start_request.length() + end_request.length() + length) + "\r\n");
    client.print("\r\n");

    // Send body
    client.print(start_request);
    client.write(image, length);
    client.print(end_request);

    // Wait for response
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") break;
    }

    String response = client.readString();
    Serial.println("Telegram response:");
    Serial.println(response);
}
