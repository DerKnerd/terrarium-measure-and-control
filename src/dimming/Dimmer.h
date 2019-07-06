//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_DIMMER_H
#define TERRARIUM_MEASURE_AND_CONTROL_DIMMER_H

#include <HID.h>

class Dimmer {
private:
    uint8_t pin;
public:
    void setup(uint8_t pin);

    void dimm(uint8_t value);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_DIMMER_H
