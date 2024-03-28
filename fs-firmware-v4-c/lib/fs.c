#include <fs.h>

#include <avr/io.h>

ISR(INT2_vect)
{
    RC_OtA_KS_STATUS = !(RC_OtA_KS_STATUS);
}

ISR(INT3_vect)
{
    FS_BUTTON_KS_STATUS = !(FS_BUTTON_KS_STATUS);
}

void fs_init(void)
{
    // Set the KS pins as inputs
    DDRG &= ~(RC_OtA_KS | FS_BUTTON_KS);

    // Set the KS pins to trigger an interrupt on a falling edge
    EICRA |= (1 << ISC21) | (1 << ISC31);
    EICRA &= ~(1 << ISC20) & ~(1 << ISC30) ;
    /*............................................*/

    // Enable the KS interrupts
    EIMSK |= (1 << INT2) | (1 << INT3);
    
}