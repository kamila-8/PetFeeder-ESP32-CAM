# 🐾 **Automatic Pet Feeder with ESP32-CAM** 🐾

This project is an **IoT-based automatic pet feeder** system powered by **ESP32-CAM**. It automates the feeding of pets using a **servo motor** and provides remote control via **MQTT** and a **Telegram bot**. The system operates in **auto mode** (feeding every 3 hours) and **manual mode** (feeding on user command via button, MQTT, or Telegram).

## 📚 **Table of Contents**

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

## 🚀 **Project Overview**

The **Automatic Pet Feeder** uses the **ESP32-CAM** module to dispense food and interact with users. The system features **3 modes**:
1. **Autonomous Mode**: Feeding occurs every 3 hours.
2. **Manual Mode**: Trigger feeding via:
   - Push button 🟢
   - MQTT commands 📲
   - Telegram bot commands 📷

The system provides **feedback** through MQTT and can send a **photo** of the pet's food bowl via the Telegram bot to confirm each action.

## ⚙️ **Hardware Requirements**

- **ESP32-CAM** (AI Thinker)
- **Servo motor** (connected to GPIO 14)
- **Push button** (GPIO 13)
- **Breadboard and jumper wires**
- **5V power supply**
- **Capacitor (470µF, 16V)**
- **Diode (100V, 3A)**
- **Resistor (10KΩ)** 

### **Hardware Connections**:
- **Servo Motor** connected to GPIO 14 (Powering through the 5V supply)
- **Push button** connected to GPIO 13


### **Wiring**:
1. Connect **servo motor** to **GPIO 14** for the food dispensing action.
2. Connect **button** to **GPIO 13** (pull-up resistor is used).
3. The **5V power** comes from the **ESP32** to power the servo and other components.
4. Use the **10kΩ pull-up resistor** on the **push button** and the **470µF capacitor** to smooth power fluctuations.
5. Connect the **diode (100V, 3A)** to prevent voltage spikes.

## 💻 **Software Requirements**

- **Visual Studio with PlatformIO extension** (used for this project)
- **Libraries**:
  - `WiFi.h` (included with ESP32 package)
  - `PubSubClient.h` (for MQTT communication)
  - `ESP32Servo.h` (for controlling the servo motor)
  - `UniversalTelegramBot.h` (for Telegram interaction)
  - `ArduinoJson.h` (for parsing JSON data)

- **MQTT Broker**: Mosquitto or any public MQTT broker
- **Telegram Bot API**: To send photos and receive commands

## 🔧 **Installation**

1. **Set up PlatformIO with Visual Studio**:
   - Install **PlatformIO** from [platformio.org](https://platformio.org/).
   - Open the **Visual Studio Code** and install the **PlatformIO** extension.
   - Open **PlatformIO Home** and select **New Project** to create the project with **ESP32-CAM** board.

2. **Install necessary libraries**:
   - In **PlatformIO**, open the **PIO Home**.
   - Go to **Libraries** > **Manage Libraries**, then search for and install the following libraries:
     - `PubSubClient` (MQTT)
     - `ESP32Servo` (for servo motor)
     - `UniversalTelegramBot` (for Telegram interaction)

3. **Clone the repository**:
   ```bash
   git clone https://github.com/kamila-8/PetFeeder-ESP32-CAM.git


Open main.cpp in PlatformIO and build the project.

Assemble the hardware:

Connect the servo to GPIO 14, the button to GPIO 13, and the ESP32-CAM for camera functionality.

Upload the code:

Connect your ESP32-CAM to your computer via USB.

In PlatformIO, select the correct Port and click Upload.

⚙️ Configuration

Wi-Fi:
Open config.h and add your Wi-Fi credentials:

#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_Password"


MQTT:
Configure the MQTT broker:

#define MQTT_BROKER "broker.emqx.io"
#define MQTT_PORT 1883
#define MQTT_USER "username"
#define MQTT_PASSWORD "password"


Telegram Bot:
Add your Telegram Bot token and Chat ID in config.h:

#define TELEGRAM_BOT_TOKEN "your-telegram-bot-token"
#define CHAT_ID "your-chat-id"

📱 Usage

Power up the ESP32 via USB.

Open Serial Monitor in PlatformIO to monitor the connection status.

Wait for the system to connect to Wi-Fi and MQTT. You should see "Connected to Wi-Fi!" and "Connected to MQTT!" in the Serial Monitor.

Control the feeder:

Manual Feeding: Press the button or send an MQTT message or use the Telegram bot.

Automatic Feeding: The system will feed every 3 hours automatically.

🐱 Telegram Bot Interaction:

Send /photo to receive a photo of the pet’s food bowl.

📂 Code Structure

main.cpp: Main application logic to handle feeding, camera control, and communication.

config.h: Wi-Fi, MQTT, and Telegram configurations.

ServoController.h/.cpp: Controls the servo motor to dispense food.

CameraManager.h/.cpp: Handles camera initialization and image capture.

MQTTClient.h/.cpp: Manages MQTT communication and subscriptions.

TelegramBot.h/.cpp: Manages Telegram bot integration for commands and image sending.

🛠️ Troubleshooting

Wi-Fi Issues:

Ensure your network operates on 2.4 GHz (ESP32 does not support 5 GHz).

Double-check your SSID and password.

MQTT Connection Failures:

Ensure the MQTT broker is running.

Verify your MQTT credentials are correct.

Servo not working:

Check the wiring for the servo motor connected to GPIO 14.

Test servo operation separately with basic code.

Telegram Bot:

Ensure the Bot Token and Chat ID are correct.

The Telegram bot can only send images, not receive messages.

🚀 Future Improvements
Add RGB LEDs for more colorful animations.

Replace servo motor with a more efficient feeding mechanism.

Integrate with Blynk for a mobile app interface.

Implement Deep Sleep Mode to reduce power consumption.

Add more detailed camera functionality for better monitoring.

📝 License
This project is licensed under the MIT License. See the LICENSE file for more details.

🙏 Acknowledgements
Politecnico di Torino for academic support.

Espressif Systems for the ESP32 documentation.

Arduino and MQTT communities for the libraries and resources.

Telegram for the Bot API.



