#include "Display.h"

void Display::setup() {
    Serial.println(F("Create epd"));
    epd = new Epd();

    Serial.println(F("Init epd"));
    if (epd->Init(lut_full_update) != 0) {
        Serial.print(F("e-Paper init failed"));
        return;
    }

    Serial.println(F("Create paint"));
    paint = new Paint(this->image, 0, 0);

    Serial.println(F("Clear frame memory"));
    clear();

    Serial.println(F("Display hello world"));
    displayText(F("Hello World"), 0);

    delay(2000);
    clear();

    Serial.println(F("Init epd"));
    if (epd->Init(lut_partial_update) != 0) {
        Serial.print(F("e-Paper init failed"));
        return;
    }
}

void Display::clear() {
    Serial.println(F("Init epd"));
    if (epd->Init(lut_full_update) != 0) {
        Serial.println(F("Clearing failed"));
        return;
    }

    epd->ClearFrameMemory(0xFF);
    epd->DisplayFrame();
    epd->ClearFrameMemory(0xFF);
    epd->DisplayFrame();

    if (epd->Init(lut_partial_update) != 0) {
        Serial.println(
                F("Clearing                                                                                                                                                                                                                                                                       failed"));
        return;
    }
}

void Display::displayText(char *text, uint8_t line) {
    this->displayText(String(text), line);
}

void Display::displayText(__FlashStringHelper *text, uint8_t line) {
    this->displayText(String(text), line);
}

void Display::displayText(const String &text, uint8_t line) {
    auto height = 288;
    auto width = 16;

    paint->SetRotate(ROTATE_270);
    paint->SetWidth(width);
    paint->SetHeight(height);

    paint->Clear(UNCOLORED);
    paint->DrawStringAt(0, 0, text.c_str(), &Font12, COLORED);

    epd->SetFrameMemory(paint->GetImage(), line * width, 288 - height, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
    epd->SetFrameMemory(paint->GetImage(), line * width, 288 - height, paint->GetWidth(), paint->GetHeight());
    epd->DisplayFrame();
}
