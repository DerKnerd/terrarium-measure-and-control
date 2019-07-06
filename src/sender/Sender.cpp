//
// Created by imanuel on 06.07.19.
//

#include "Sender.h"

void Sender::setup(const uint8_t pin) {
    EEPROM.begin();
    nodeId = generateNodeId();
    transmitter = new RFTransmitter(pin, nodeId);

    StaticJsonDocument<39> doc;
    doc["action"] = "register";
    doc["nodeId"] = nodeId;

    send(doc);
}

void Sender::send(JsonDocument data) {
    String output;
    serializeMsgPack(data, output);

    transmitter->send((byte *) output.c_str(), output.length());
}

byte Sender::generateNodeId() {
    auto eepromId = EEPROM.read(0);
    if (eepromId <= 200 && eepromId >= 10) {
        return eepromId;
    }

    randomSeed(analogRead(A0));
    byte id = random(10, 200);
    EEPROM.update(0, id);

    return id;
}
