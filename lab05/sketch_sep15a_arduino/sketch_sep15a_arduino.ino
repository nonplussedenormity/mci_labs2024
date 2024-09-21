#include <Servo.h>

Servo s1;

void setup() {
    Serial.begin(1200); // Initialize Serial communication
    s1.attach(9);
    Serial.println("It works"); // Print message to Serial Monitor
}

void loop() {
    s1.write(0);
}
