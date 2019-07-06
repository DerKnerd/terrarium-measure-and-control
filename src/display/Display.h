//
// Created by imanuel on 06.07.19.
//

#ifndef TERRARIUM_MEASURE_AND_CONTROL_DISPLAY_H
#define TERRARIUM_MEASURE_AND_CONTROL_DISPLAY_H

#include <U8x8lib.h>

class Display {
private:
    U8X8_SH1106_128X64_NONAME_HW_I2C *screen;
public:
    void setup();

    void clear();

    void displayText(byte line, const char *text);
};


#endif //TERRARIUM_MEASURE_AND_CONTROL_DISPLAY_H
