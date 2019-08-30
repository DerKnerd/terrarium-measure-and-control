//
// Created by imanuel on 06.07.19.
//

#include "DimmerControl.h"

void DimmerControl::setup(const uint8_t pin, const uint8_t pin2) {
    this->pin = pin;
    this->pin2 = pin2;
    pinMode(pin, OUTPUT);
    pinMode(pin2, OUTPUT);
    reset();
}

void DimmerControl::dimm(const uint8_t value) {
    analogWrite(pin, value);
    analogWrite(pin2, value);
}

void DimmerControl::dimmUp() {
    if (dimmStatus < 255) {
        dimm(dimmStatus);
        dimmStatus++;
    }
}

void DimmerControl::dimmDown() {
    if (dimmStatus > 0) {
        dimm(dimmStatus);
        dimmStatus--;
    }
}

void DimmerControl::reset() {
    dimmStatus = 0;
    dimm(dimmStatus);
}
