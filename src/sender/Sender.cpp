//
// Created by imanuel on 06.07.19.
//

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <eeprom/EEPROMAccess.h>
#include "Sender.h"

void Sender::setup(uint8_t txPin, uint8_t rxPin) {
    Serial.println(F("Init ESP8266"));
    EEPROM.begin();
    auto serial = new SoftwareSerial(txPin, rxPin);
    esp8266 = new ESP8266(*serial);
    auto ssid = EEPROMAccess::readString(0);
    auto passphrase = EEPROMAccess::readString(34);
    esp8266->setOprToStationSoftAP();
    esp8266->joinAP(ssid, passphrase);
    esp8266->enableMUX();
    esp8266->startTCPServer(8080);
    esp8266->setTCPServerTimeout(10);
}

String Sender::getIp() {
    return esp8266->getLocalIP();
}
