//
// Created by imanuel on 06.07.19.
//

#include "Display.h"

void Display::displayText(const byte line, const char *text) {
    screen->clearLine(line);
    screen->drawString(0, line, text);
}

void Display::setup() {
    screen = new U8X8_SH1106_128X64_NONAME_HW_I2C(U8X8_PIN_NONE);

    screen->begin();
    screen->setFont(u8x8_font_chroma48medium8_r);
    screen->setPowerSave(0);
}

void Display::clear() {
    screen->clearDisplay();
}
