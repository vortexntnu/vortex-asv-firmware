#include <BUTTON.h>

namespace BUTTON{
    
    void init() {
        pinMode(BUTTON_PIN, INPUT);
    }

    bool get_state() {
        return digitalRead(BUTTON_PIN);
    }

}
