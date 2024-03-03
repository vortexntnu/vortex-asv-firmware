#include "../lib/status_light/status_light.h"
#include "../lib/fs/fs.h"
#include "../lib/i2c/i2c.h"
#include "../lib/esc_driver/esc_driver.h"

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
    set_esc_speed(thrusters_values[0], thrusters_values[1], thrusters_values[2], thrusters_values[3]);
  }
}
