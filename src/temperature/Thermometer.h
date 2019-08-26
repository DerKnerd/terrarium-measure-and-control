//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_THERMOMETER_H
#define TERRARIUM_MEASURE_AND_CONTROL_THERMOMETER_H

#include <HID.h>
#include <display/Display.h>
#include <DallasTemperature.h>

class Thermometer {
private:
    DallasTemperature *dallasTemperature;
    uint8_t pin;
    uint8_t oneWireIndex;

public:
    void setup(uint8_t pin, uint8_t oneWireIndex);

    float getTemperature();
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_THERMOMETER_H
