//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_SENDER_H
#define TERRARIUM_MEASURE_AND_CONTROL_SENDER_H

#include <ArduinoJson.h>
#include <RFTransmitter.h>
#include <EEPROM.h>

class Sender {
private:
    RFTransmitter *transmitter;
    byte nodeId;

    byte generateNodeId();

public:
    void setup(uint8_t pin);

    void send(JsonDocument data);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_SENDER_H
