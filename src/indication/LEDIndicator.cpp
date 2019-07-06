//
// Created by imanuel on 06.07.19.
//

#include "LEDIndicator.h"

void LEDIndicator::startIndicating() {
    indicating = true;
    digitalWrite(pin, HIGH);
}

void LEDIndicator::stopIndicating() {
    indicating = false;
    digitalWrite(pin, LOW);
}

void LEDIndicator::setup(const int pin) {
    LEDIndicator::pin = pin;
    indicating = false;
    threshold = 5000;
    lastMillis = 0;
    pinMode(LEDIndicator::pin, OUTPUT);
}

void LEDIndicator::loop() {
    if (indicating && millis() - lastMillis > threshold) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}
