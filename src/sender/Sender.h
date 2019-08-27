//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_SENDER_H
#define TERRARIUM_MEASURE_AND_CONTROL_SENDER_H

#define ESP8266_USE_SOFTWARE_SERIAL

#include <ArduinoJson.h>
#include <ESP8266.h>

class Sender {
private:
    ESP8266 *esp8266;

public:
    void setup(uint8_t txPin, uint8_t rxPin);

    String getIp();
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_SENDER_H
