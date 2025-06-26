#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <ESP32Servo.h>  

// ServoController class handles servo motor operations for feeder door
class ServoController {
public:
    ServoController(int pin);  // Constructor to set servo control pin
    void open();  // Opens the feeder door
    void close(); // Closes the feeder door

private:
    Servo servo;
    int servoPin;
};

#endif


