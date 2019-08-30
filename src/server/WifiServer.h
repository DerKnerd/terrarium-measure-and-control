//
// Created by imanuel on 30.08.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_WIFISERVER_H
#define TERRARIUM_MEASURE_AND_CONTROL_WIFISERVER_H

#include <SPI.h>
#include <WiFiNINA.h>

class WifiServer {
public:
    void setup();

    void handleRequest(uint8_t hotSideTemp, uint8_t coldSideTemp, uint8_t humidity, uint8_t time);

private:
    WifiServer *server;
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_WIFISERVER_H
