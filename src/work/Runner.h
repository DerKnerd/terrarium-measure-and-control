//
// Created by imanuel on 28.08.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H
#define TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H

#include <Arduino.h>
#include "../display/Display.h"
#include "../humidity/HumiditySensor.h"
#include "../temperature/Thermometer.h"
#include "../dimming/DimmerControl.h"
#include "../relay/Relay.h"
#include "../timing/Clock.h"

#define DIMM_CHANGE_THRESHOLD_MILLIS = ((22.0 - 8) / 2) * 60 * 60 * 1000.0;

class Runner {
public:
    void setup();

    void loop();

private:
    Display *display = new Display();
    HumiditySensor *humiditySensor = new HumiditySensor();
    Thermometer *thermometer = new Thermometer();
    DimmerControl *dimmer = new DimmerControl();
    Relay *relay = new Relay();
    Clock *clock = new Clock();

    unsigned long displayTempMillis = millis();
    unsigned long displayTimeMillis = millis();
    unsigned long dimmMillis = millis();
    bool showTimeSeparator = false;

    float oldColdTemp = 0.0f;
    float oldHotTemp = 0.0f;
    float oldHumidity = 0.0f;

    void handleHotSideTemperature(uint8_t value);

    void handleColdSideTemperature(uint8_t value);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H
