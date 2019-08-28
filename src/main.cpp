//
// Created by imanuel on 06.07.19.
//

#include <Arduino.h>
#include <work/Runner.h>

auto runner = new Runner();

void setup() {
    runner->setup();
}

void loop() {
    runner->loop();
}
