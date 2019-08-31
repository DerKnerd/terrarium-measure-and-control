//
// Created by imanuel on 28.08.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H
#define TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H

#include <Arduino.h>
#include <server/PrometheusServer.h>
#include "../display/Display.h"
#include "../humidity/HumiditySensor.h"
#include "../temperature/Thermometer.h"
#include "../dimming/DimmerControl.h"
#include "../relay/Relay.h"
#include "../timing/Clock.h"

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
    PrometheusServer *prometheusServer = new PrometheusServer();

    unsigned long displayTempMillis = millis();
    bool showTimeSeparator = false;

    float oldColdTemp = 0.0f;
    float oldHotTemp = 0.0f;
    float oldHumidity = 0.0f;

    void handleHotSideTemperature(uint8_t value);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_RUNNER_H
