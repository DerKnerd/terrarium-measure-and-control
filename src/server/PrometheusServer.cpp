//
// Created by imanuel on 30.08.19.
//

#include "PrometheusServer.h"

void PrometheusServer::handleRequest(
        const uint8_t hotSideTemp,
        const uint8_t coldSideTemp,
        const uint8_t humidity,
        const String &time
) {
    Serial.println(F("Check if server is available"));
    auto client = server->available();
    if (client) {
        Serial.println(F("Server is available"));
        if (client.connected()) {
            Serial.println(F("Client is connected"));

            Serial.println(F("Writing hot side"));
            client.println(F("HELP ardu_terra_hot_side The temperature on the hot side of the terrarium"));
            client.println(F("TYPE ardu_terra_hot_side gauge"));
            client.print(F("ardu_terra_hot_side{who=\""));
            client.print(WHOISTHIS);
            client.print(F("\"} "));
            client.println(hotSideTemp);

            Serial.println(F("Writing cold side"));
            client.println(F("HELP ardu_terra_cold_side The temperature on the cold side of the terrarium"));
            client.println(F("TYPE ardu_terra_cold_side gauge"));
            client.print(F("ardu_terra_cold_side{who=\""));
            client.print(WHOISTHIS);
            client.print(F("\"} "));
            client.println(coldSideTemp);

            Serial.println(F("Writing humidity"));
            client.println(F("HELP ardu_terra_humidity The humidity of the terrarium"));
            client.println(F("TYPE ardu_terra_humidity gauge"));
            client.print(F("ardu_terra_humidity{who=\""));
            client.print(WHOISTHIS);
            client.print(F("\"} "));
            client.println(humidity);
        }
    }
}

void PrometheusServer::setup() {
    server = new WiFiServer(80);

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        connected = false;
        return;
    }

    auto fv = WiFiClass::firmwareVersion();
    if (fv < "1.0.0") {
        Serial.println("Please upgrade the firmware");
        connected = false;
        return;
    }

    int status = WL_IDLE_STATUS;

    Serial.println(F("Scanning for networks..."));
    Serial.print(WiFi.scanNetworks());
    Serial.println(F(" networks found"));

    uint8_t macAddress[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(macAddress);

    Serial.print(F("MAC address: "));
    for (unsigned char segment : macAddress) {
        Serial.print(String(segment));
    }
    Serial.println();

    auto tries = 0;
    while (status != WL_CONNECTED) {
        tries++;
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(SSID, PASSPRHASE);

        // wait 10 seconds for connection:
        delay(10000);
        if (tries == 10) {
            Serial.print(F("Could not connect to "));
            Serial.println(SSID);
            Serial.println(F("Working without WiFi"));
            break;
        }
    }

    if (tries < 10) {
        Serial.print(F("Connected to SSID "));
        Serial.println(SSID);
    }

    server->begin();
}

IPAddress PrometheusServer::getIpAddress() {
    return WiFi.localIP();
}
