//
// Created by imanuel on 27.08.19.
//

#include "EEPROMAccess.h"

void EEPROMAccess::writeString(int32_t position, const String &data) {
    EEPROM.begin();
    auto _size = data.length();
    for (int32_t i = 0; i < _size; i++) {
        EEPROM.write(position + i, data[i]);
    }
    EEPROM.write(position + _size, '\0');
}

String EEPROMAccess::readString(int32_t position) {
    EEPROM.begin();
    char data[100];
    auto len = 0;
    auto k = EEPROM.read(position);
    while (k != '\0' && len < 500) {
        k = EEPROM.read(position + len);
        data[len] = k;
        len++;
    }

    data[len] = '\0';

    return String(data);
}
