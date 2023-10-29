#include <Arduino.h>

#define BUTTON_PIN 11

namespace BUTTON{
    void init();

    bool get_state();
}

