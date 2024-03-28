
#include <avr/io.h>
#include <util/delay.h>

#include "fs.h"
#include "i2c.h"
#include "status_light.h"
#include "esc_driver.h"



#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

int main(void)
{
  fs_init();

  timers_init();

  TWI_init();

  LED_init();
  _delay_ms(500);
  test_leds();
  _delay_ms(500);
  test_rgby();
  _delay_ms(500);

  arm_esc();

  while(1)
  {
    set_esc_speed(thrusters_values_g[0], thrusters_values_g[1], thrusters_values_g[2], thrusters_values_g[3]);
  }
}
