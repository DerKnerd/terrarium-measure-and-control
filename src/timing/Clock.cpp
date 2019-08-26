//
// Created by imanuel on 08.07.19.
//

#include "Clock.h"

void Clock::setup() {
    auto rtc = new RTC_DS3231();
    rtc->begin();
}

DateTime Clock::getTime() {
    auto now = RTC_DS3231::now();

    return now;
}
