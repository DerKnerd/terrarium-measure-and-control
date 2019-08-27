//
// Created by imanuel on 27.08.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_EEPROMACCESS_H
#define TERRARIUM_MEASURE_AND_CONTROL_EEPROMACCESS_H

#include <EEPROM.h>
#include <WString.h>

class EEPROMAccess {
public:
    static String readString(int32_t position);

    static void writeString(int32_t position, const String &data);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_EEPROMACCESS_H
