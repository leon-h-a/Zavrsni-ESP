#include <Arduino.h>

byte receivedByte;

void setup() {
    Serial.begin(9600);
//    while (!Serial) {
//        ; // wait for serial port to connect. Needed for Native USB only
//    }
}

void loop() {
    if (Serial.available() > 0) {
        receivedByte = Serial.read();
        Serial.println("Primio sam: ");
        Serial.print(receivedByte);
    }

    else{
        Serial.print("Nista\n");
    }

    delay(1000);
}