//
// Created by imanuel on 06.07.19.
//

#include "DimmerControl.h"

void DimmerControl::setup(const uint8_t pin) {
    this->pin = pin;
}

void DimmerControl::dimm(const uint8_t value) {
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
