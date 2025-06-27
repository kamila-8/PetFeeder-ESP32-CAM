# 🐾 Automatic Pet Feeder with ESP32-CAM 🐾

This project is an **IoT-based automatic pet feeder** powered by **ESP32-CAM**. It automates pet feeding using a **servo motor** and provides remote control via **MQTT** and **Telegram bot**. The system has **auto mode** (feeds every 3 hours) and **manual mode** (feeds on user command via button, MQTT, or Telegram).

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Troubleshooting](#troubleshooting)
- [Future Improvements](#future-improvements)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Project Overview

The **Automatic Pet Feeder** uses the **ESP32-CAM** module to dispense food and interact with users. It supports three modes:

1. **Autonomous Mode**: Feeds every 3 hours.
2. **Manual Mode**: Trigger feeding via:
   - Push button 🟢
   - MQTT commands 📲
   - Telegram bot commands 📷

System provides **feedback** via MQTT and sends a **photo** of the food bowl via Telegram to confirm actions.

## Hardware Requirements

- **ESP32-CAM** (AI Thinker)
- **Servo motor** (GPIO 14)
- **Push button** (GPIO 13)
- **Breadboard and jumper wires**
- **5V power supply**
- **Capacitor (470µF, 16V)**
- **Diode (100V, 3A)**
- **Resistor (10KΩ)**

### Hardware Connections

1. **Servo** → GPIO 14  
2. **Button** → GPIO 13 with pull-up resistor  
3. **Power** → 5V (from ESP32)  
4. **Resistor** → 10kΩ for pull-up on button  
5. **Capacitor** → 470µF for power smoothing  
6. **Diode** → 100V, 3A to suppress spikes

## Software Requirements

- **Visual Studio Code + PlatformIO extension**
- **Libraries**:
  - `WiFi.h`
  - `PubSubClient.h`
  - `ESP32Servo.h`
  - `UniversalTelegramBot.h`
  - `ArduinoJson.h`
- **MQTT Broker** (e.g., Mosquitto or EMQX)
- **Telegram Bot API**

## Installation

### 1. Set up PlatformIO

- Download and install [PlatformIO](https://platformio.org/)
- Install the PlatformIO extension in Visual Studio Code.
- Create a new project for **ESP32-CAM**.

### 2. Install Libraries

In PlatformIO > Libraries:
- Search and install:
  - `PubSubClient`
  - `ESP32Servo`
  - `UniversalTelegramBot`

### 3. Clone the Repository

```bash
git clone https://github.com/kamila-8/PetFeeder-ESP32-CAM.git
```

- Open `main.cpp` in PlatformIO.
- Connect your ESP32-CAM via USB.
- Select correct COM port and click Upload.

## Configuration

### Wi-Fi

Edit `config.h`:

```cpp
#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_Password"
```

### MQTT

```cpp
#define MQTT_BROKER "broker.emqx.io"
#define MQTT_PORT 1883
#define MQTT_USER "username"
#define MQTT_PASSWORD "password"
```

### Telegram Bot

```cpp
#define TELEGRAM_BOT_TOKEN "your-telegram-bot-token"
#define CHAT_ID "your-chat-id"
```

## Usage

1. Power the ESP32 via USB.
2. Open Serial Monitor in PlatformIO.
3. Watch for status:
   - "Connected to Wi-Fi!"
   - "Connected to MQTT!"

### Control Options

- **Manual**: Press the button / MQTT / Telegram command
- **Auto**: Every 3 hours

### Telegram Bot Commands

- `/photo` → Sends a photo from the ESP32-CAM

## Code Structure

- `main.cpp` → Application logic
- `config.h` → Wi-Fi, MQTT, Telegram configs
- `ServoController.h/.cpp` → Servo logic
- `CameraManager.h/.cpp` → Camera control
- `MQTTClient.h/.cpp` → MQTT logic
- `TelegramBot.h/.cpp` → Telegram interaction

## Troubleshooting

### Wi-Fi

- Ensure network is 2.4GHz
- Verify SSID and password

### MQTT

- Ensure broker is running
- Double-check credentials

### Servo

- Check GPIO 14 wiring
- Test with basic code

### Telegram

- Ensure Token and Chat ID are valid
- Only image **sending** supported

## Future Improvements

- Add RGB LEDs
- Better feeding mechanism
- Blynk integration
- Deep Sleep Mode
- Enhanced camera features

## License

MIT License. See [LICENSE](LICENSE) file.

## Acknowledgements

- Politecnico di Torino
- Espressif Systems (ESP32 docs)
- Arduino + MQTT communities
- Telegram Bot API




