//
// Created by imanuel on 30.08.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_PROMETHEUSSERVER_H
#define TERRARIUM_MEASURE_AND_CONTROL_PROMETHEUSSERVER_H

#include <SPI.h>
#include <WiFiNINA.h>
#include <WhoIsThis.h>
#include <WifiSecrets.h>

class PrometheusServer {
public:
    void setup();

    void handleRequest(uint8_t hotSideTemp, uint8_t coldSideTemp, uint8_t humidity, const String &time);

    IPAddress getIpAddress();

private:
    WiFiServer *server;
    bool connected = false;
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_PROMETHEUSSERVER_H
