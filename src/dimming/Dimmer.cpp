//
// Created by imanuel on 06.07.19.
//

#include "Dimmer.h"

void Dimmer::setup(const uint8_t pin) {
    this->pin = pin;
}

void Dimmer::dimm(const uint8_t value) {
    analogWrite(pin, value);
}
