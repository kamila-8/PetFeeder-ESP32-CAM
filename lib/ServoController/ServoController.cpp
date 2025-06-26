#include "ServoController.h"

ServoController::ServoController(int pin) : servoPin(pin) {}


void ServoController::open() {
    servo.attach(servoPin);
    servo.write(90);
    delay(2000);   
    servo.detach();
}


void ServoController::close() {
    servo.attach(servoPin);
    servo.write(0);
    delay(500);     
    servo.detach();
}

