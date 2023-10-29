#include <BUZZER.h>

namespace BUZZER{
    
    void Buzzer_init() {
        pinMode(buzzerPin, OUTPUT);
        pinMode(switchPin, INPUT);
    }

    void Set_Buzzer(bool state){
        if (state == true){
            tone(buzzerPin, 1000);
        }else{
            noTone(buzzerPin);
        }
    }

}
