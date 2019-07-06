//
// Created by imanuel on 06.07.19.
//

#include <Arduino.h>
#include <indication/LEDIndicator.h>
#include <display/Display.h>
#include <humidity/HumiditySensor.h>
#include <sender/Sender.h>
#include <temperature/Thermometer.h>
#include <dimming/Dimmer.h>
#include <relay/Relay.h>

const auto ledIndicator = new LEDIndicator();
const auto display = new Display();
const auto humiditySensor = new HumiditySensor();
const auto sender = new Sender();
const auto hotSideThermometer = new Thermometer();
const auto coldSideThermometer = new Thermometer();
const auto dimmer = new Dimmer();
const auto relay = new Relay();

auto lastMillis = millis();
auto oldColdTemp = 0.0f;
auto oldHotTemp = 0.0f;
auto oldHumidity = 0.0f;

void handleHotSideTemperature(const uint8_t value) {
    if (value < 40) {
        String data;
        data.concat(F("Temp alert "));
        data.concat(value);
        display->displayText(6, data.c_str());
        relay->turnOn();
    } else {
        relay->turnOff();
    }
}

void handleColdSideTemperature(const uint8_t value) {
    if (value < 30) {
        String data;
        data.concat(F("Temp alert "));
        data.concat(value);
        display->displayText(6, data.c_str());
        relay->turnOn();
    }
}

void setup() {
    ledIndicator->setup(6);
    display->setup();
    display->displayText(0, "Initializing...");
    ledIndicator->startIndicating();

    humiditySensor->setup(2);
    hotSideThermometer->setup(4);
    coldSideThermometer->setup(5);
    sender->setup(3);
    dimmer->setup(11);
    relay->setup(8);
    Serial.begin(9600);

    ledIndicator->stopIndicating();
    display->clear();
}

void loop() {
    ledIndicator->loop();

    auto hotSide = hotSideThermometer->getTemperature();
    auto coldSide = coldSideThermometer->getTemperature();
    auto humidity = humiditySensor->getHumidity();

    if (millis() - lastMillis > 5000) {
        if (hotSide != oldHotTemp) {
            display->displayText(0, "Hot Side:");

            String hotSideText;
            hotSideText.concat(hotSide);
            hotSideText.concat(F(" C"));
            display->displayText(1, hotSideText.c_str());
            oldHotTemp = hotSide;

            handleHotSideTemperature(hotSide);
        }

        if (coldSide != oldColdTemp) {
            display->displayText(2, "Cold Side:");

            String coldSideText;
            coldSideText.concat(coldSide);
            coldSideText.concat(F(" C"));
            display->displayText(3, coldSideText.c_str());
            oldColdTemp = coldSide;

            handleColdSideTemperature(coldSide);
        }

        if (humidity != oldHumidity) {
            display->displayText(4, "Humidity:");

            String humidityText;
            humidityText.concat(humidity);
            humidityText.concat(F(" %"));
            display->displayText(5, humidityText.c_str());
            oldHumidity = humidity;
        }

        lastMillis = millis();
    }

    auto jsonDoc = DynamicJsonDocument(200);
    jsonDoc["action"] = F("data");
    jsonDoc["hotSide"] = hotSide;
    jsonDoc["coldSide"] = coldSide;
    jsonDoc["humidity"] = humidity;

    sender->send(jsonDoc);
}