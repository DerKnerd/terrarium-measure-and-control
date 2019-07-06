//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_LEDINDICATOR_H
#define TERRARIUM_MEASURE_AND_CONTROL_LEDINDICATOR_H

#include <Arduino.h>

class LEDIndicator {
private:
    int lastMillis;
    int pin;
    unsigned long threshold;
    bool indicating;
public:
    void startIndicating();

    void stopIndicating();

    void setup(int pin);

    void loop();
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_LEDINDICATOR_H
