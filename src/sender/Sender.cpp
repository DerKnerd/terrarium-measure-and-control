//
// Created by imanuel on 06.07.19.
//

#include "Sender.h"

void Sender::setup(const uint8_t pin) {
    Serial.println(F("Init EEPROM"));
    EEPROM.begin();

    Serial.println(F("Generate node id"));
    nodeId = generateNodeId();

    Serial.print(F("Node id is: "));
    Serial.println(nodeId);

    Serial.println(F("Init RFTransmitter"));
    transmitter = new RFTransmitter(pin, nodeId);

    Serial.println(F("Create json doc"));
    auto doc = DynamicJsonDocument(39);
    doc["action"] = "register";
    doc["nodeId"] = nodeId;

    Serial.println(F("Send register json"));
    send(doc);
}

void Sender::send(const DynamicJsonDocument &data) {
    Serial.println(F("Create msg pack data"));
    String output;
    serializeMsgPack(data, output);

    Serial.print(F("Serialized data"));
    Serial.println(output);

    Serial.println(F("Send data via transmitter"));
    transmitter->print(const_cast<char *>(output.c_str()));
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
