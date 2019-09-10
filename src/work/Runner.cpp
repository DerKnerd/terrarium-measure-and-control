//
// Created by imanuel on 28.08.19.
//

#include "Runner.h"

void Runner::setup() {
    Serial.begin(9600);
    Serial.println(F("Initializing..."));

    Serial.println(F("Initializing display"));
    display->setup();
    display->displayText(F("Initializing..."), 0);

    Serial.println(F("Initializing clock"));
    display->displayText(F("Initializing clock"), 1);
    Clock::setup();

    Serial.println(F("Initializing humidity sensor"));
    display->displayText(F("Initializing humidity sensor"), 2);
    humiditySensor->setup(2);

    Serial.println(F("Initializing dimmer"));
    display->displayText(F("Initializing dimmer"), 3);
    dimmer->setup(3, 5);
    dimmer->reset();

    Serial.println(F("Initializing temperatures"));
    display->displayText(F("Initializing temperatures"), 4);
    thermometer->setup(4);

    Serial.println(F("Initializing relay"));
    display->displayText(F("Initializing relay"), 5);
    relay->setup(6);

    display->displayText(F("Finish setup"), 7);
    display->clear();
}

void Runner::loop() {
    Serial.println(F("Start loop"));
    const auto coldSide = thermometer->getTemperature(0);
    const auto hotSide = thermometer->getTemperature(1);
    const auto humidity = humiditySensor->getHumidity();

    auto now = Clock::getTime();
    if (now.hour() == 8 || now.hour() == 9 || now.hour() == 10) {
        dimmer->dimmUp();
        handleHotSideTemperature(hotSide);
    } else if (now.hour() == 20 || now.hour() == 21 || now.hour() == 22) {
        dimmer->dimmDown();
        handleHotSideTemperature(hotSide);
    } else if (now.hour() > 22 || now.hour() < 8) {
        dimmer->reset();
    } else {
        dimmer->dimm(255);
        handleHotSideTemperature(hotSide);
    }

    auto currentMillis = millis();
    if (currentMillis - displayTempMillis >= 1000) {
        if (currentMillis - cleanDisplayMillis >= 600000) {
            Serial.println(currentMillis - cleanDisplayMillis);
            display->clear();
            cleanDisplayMillis = currentMillis;
        }

        Serial.println(F("Display hot side temperature"));
        String hotSideText = F("Hot Side:  ");
        hotSideText.concat(hotSide);
        hotSideText.concat(F(" C"));
        display->displayText(hotSideText, 2);
        Serial.println(hotSideText);

        Serial.println(F("Display cold side temperature"));
        String coldSideText = F("Cold Side: ");
        coldSideText.concat(coldSide);
        coldSideText.concat(F(" C"));
        display->displayText(coldSideText, 3);
        Serial.println(coldSideText);

        Serial.println("Display humidity");
        String humidityText = F("Humidity:  ");
        humidityText.concat(humidity);
        humidityText.concat(F(" %"));
        display->displayText(humidityText, 4);
        Serial.println(humidityText);

        displayTempMillis = millis();
    }

    String time = "Time: ";
    time.concat(now.hour());
    if (showTimeSeparator) {
        time.concat(":");
    } else {
        time.concat(" ");
    }

    time.concat(now.minute());
    showTimeSeparator = !showTimeSeparator;

    Serial.println(time);
    display->displayText(time, 0);
}

void Runner::handleHotSideTemperature(const uint8_t value) {
    if (value < 40) {
        relay->turnOn();
    } else if (value > 50) {
        relay->turnOff();
    }
}