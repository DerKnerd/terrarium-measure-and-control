//
// Created by imanuel on 08.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_CLOCK_H
#define TERRARIUM_MEASURE_AND_CONTROL_CLOCK_H

#include <RTClib.h>

class Clock {
public:
    void setup();

    DateTime getTime();
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_CLOCK_H
