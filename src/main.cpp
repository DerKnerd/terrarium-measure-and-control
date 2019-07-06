//
// Created by imanuel on 06.07.19.
//

#include <Arduino.h>
#include <indication/LEDIndicator.h>
#include <display/Display.h>
#include <humidity/HumiditySensor.h>
#include <sender/Sender.h>
#include <temperature/Thermometer.h>

const auto ledIndicator = new LEDIndicator();
const auto display = new Display();
const auto humiditySensor = new HumiditySensor();
const auto sender = new Sender();
const auto hotSideThermometer = new Thermometer();
const auto coldSideThermometer = new Thermometer();

auto lastMillis = millis();
auto oldColdTemp = 0.0f;
auto oldHotTemp = 0.0f;
auto oldHumidity = 0.0f;

void setup() {
    ledIndicator->setup(6);
    display->setup();
    display->displayText(0, "Initializing...");
    ledIndicator->startIndicating();

    humiditySensor->setup(2);
    hotSideThermometer->setup(4);
    coldSideThermometer->setup(5);
    sender->setup(3);
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
            String hotSideText;
            hotSideText.concat(F("Hot:  "));
            hotSideText.concat(coldSide);
            hotSideText.concat(F(" "));
            hotSideText.concat((char) 223);
            hotSideText.concat(F("C"));
            display->displayText(0, hotSideText.c_str());
            oldHotTemp = hotSide;
        }

        if (coldSide != oldColdTemp) {
            String coldSideText;
            coldSideText.concat(F("Cold: "));
            coldSideText.concat(coldSide);
            coldSideText.concat(F(" "));
            coldSideText.concat((char) 223);
            coldSideText.concat(F("C"));
            display->displayText(1, coldSideText.c_str());
            oldColdTemp = coldSide;
        }

        if (humidity != oldHumidity) {
            String humidityText;
            humidityText.concat(F("Humi: "));
            humidityText.concat(humidity);
            humidityText.concat(F(" %"));
            display->displayText(2, humidityText.c_str());
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