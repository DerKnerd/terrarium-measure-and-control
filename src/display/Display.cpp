#include "Display.h"

void Display::setup() {
    Serial.println(F("Create epd"));
    epd = new Epd();

    Serial.println(F("Create paint"));
    paint = new Paint(this->image, 0, 0);

    Serial.println(F("Init epd"));
    if (epd->Init(lut_partial_update) != 0) {
        Serial.print(F("e-Paper init failed"));
        return;
    }

    Serial.println(F("Clear frame memory"));
    epd->ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd->DisplayFrame();
    epd->ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd->DisplayFrame();

    Serial.println(F("Set width and height"));
    displayText("Hello World", 0);

    delay(2000);

    if (epd->Init(lut_partial_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }
}

void Display::clear() {
    this->epd->ClearFrameMemory(0xFF);
    this->epd->DisplayFrame();
    this->epd->ClearFrameMemory(0xFF);
    this->epd->DisplayFrame();
}

void Display::displayText(char *text, uint8_t line) {
    this->displayText(String(text), line);
}

void Display::displayText(__FlashStringHelper *text, uint8_t line) {
    this->displayText(String(text), line);
}

void Display::displayText(const String &text, uint8_t line) {
    paint->SetRotate(ROTATE_90);
    paint->SetWidth(16);
    paint->SetHeight(200);

    paint->Clear(UNCOLORED);
    paint->DrawStringAt(0, 0, text.c_str(), &Font12, COLORED);
    byte insertLine = 0;
    switch (line) {
        case 0:
            insertLine = 7;
            break;
        case 1:
            insertLine = 6;
            break;
        case 2:
            insertLine = 5;
            break;
        case 3:
            insertLine = 4;
            break;
        case 4:
            insertLine = 3;
            break;
        case 5:
            insertLine = 2;
            break;
        case 6:
            insertLine = 1;
            break;
        case 7:
            insertLine = 0;
            break;
    }
    epd->SetFrameMemory(paint->GetImage(), insertLine * 16 - 24, 0, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
    epd->SetFrameMemory(paint->GetImage(), insertLine * 16 - 24, 0, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
}

void Display::displayTextTopRight(const String &text) {
    paint->SetRotate(ROTATE_90);
    paint->SetWidth(16);
    paint->SetHeight(96);

    paint->Clear(UNCOLORED);
    paint->DrawStringAt(0, 0, text.c_str(), &Font12, COLORED);
    epd->SetFrameMemory(paint->GetImage(), -8, 200, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
    epd->SetFrameMemory(paint->GetImage(), -8, 200, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
}
