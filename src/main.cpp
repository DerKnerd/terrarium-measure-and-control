//
// Created by imanuel on 06.07.19.
//

#include <Arduino.h>
#include <display/Display.h>
#include <humidity/HumiditySensor.h>
#include <sender/Sender.h>
#include <temperature/Thermometer.h>
#include <dimming/DimmerControl.h>
#include <relay/Relay.h>
#include <timing/Clock.h>

const auto display = new Display();
const auto humiditySensor = new HumiditySensor();
const auto sender = new Sender();
const auto hotSideThermometer = new Thermometer();
const auto coldSideThermometer = new Thermometer();
const auto dimmer = new DimmerControl();
const auto relay = new Relay();
const auto clock = new Clock();

auto displayTempMillis = millis();
auto dimmMillis = millis();

auto oldColdTemp = 0.0f;
auto oldHotTemp = 0.0f;
auto oldHumidity = 0.0f;

const auto dimmChangeThresholdMillis = ((22 - 8) / 2) * 60 * 60 * 1000;

void handleHotSideTemperature(const uint8_t value) {
    if (value < 40) {
        relay->turnOn();
    } else {
        relay->turnOff();
    }
}

void handleColdSideTemperature(const uint8_t value) {
    if (value < 30) {
        relay->turnOn();
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("Init display"));

    display->setup();
    display->clear();
    display->displayText(F("Initializing..."), 0);

    Serial.println(F("Init clock"));
    clock->setup();

    Serial.println(F("Init humidity sensor"));
    humiditySensor->setup(2);

    Serial.println(F("Init dimmer"));
    dimmer->setup(3);

    Serial.println(F("Init sender"));
    sender->setup(4);

    Serial.println(F("Init temperatures"));
    coldSideThermometer->setup(5, 0);
    hotSideThermometer->setup(5, 1);

    Serial.println(F("Init relay"));
    relay->setup(6);

    display->clear();
}

void loop() {
    Serial.println("Start loop");
    const auto hotSide = hotSideThermometer->getTemperature();
    const auto coldSide = coldSideThermometer->getTemperature();
    const auto humidity = humiditySensor->getHumidity();

//    const auto now = clock->getTime();
//    const auto dimmChangeThresholdMillis = ((22 - 8) / 2) * 60 * 60 * 1000;
//    if (millis() - dimmMillis > dimmChangeThresholdMillis) {
//        dimmer->dimmUp();
//    }
//    display->displayText(String(now.hour()) + ":" + String(now.minute()), 1);

    if (millis() - displayTempMillis > 5000) {
        if (hotSide != oldHotTemp) {
            display->displayText(F("Hot Side:"), 2);

            String hotSideText;
            hotSideText.concat(hotSide);
            hotSideText.concat(F(" C"));
            display->displayText(hotSideText, 3);
            oldHotTemp = hotSide;

            handleHotSideTemperature(hotSide);
        }

        if (coldSide != oldColdTemp) {
            display->displayText(F("Cold Side:"), 4);

            String coldSideText;
            coldSideText.concat(coldSide);
            coldSideText.concat(F(" C"));
            display->displayText(coldSideText, 5);
            oldColdTemp = coldSide;

            handleColdSideTemperature(coldSide);
        }

        if (humidity != oldHumidity) {
            display->displayText(F("Humidity:"), 6);

            String humidityText;
            humidityText.concat(humidity);
            humidityText.concat(F(" %"));
            display->displayText(humidityText, 7);
            oldHumidity = humidity;
        }

        displayTempMillis = millis();
    }

    auto jsonDoc = DynamicJsonDocument(200);
    jsonDoc[F("action")] = F("data");
    jsonDoc[F("hotSide")] = hotSide;
    jsonDoc[F("coldSide")] = coldSide;
    jsonDoc[F("humidity")] = humidity;

    sender->send(jsonDoc);
}
