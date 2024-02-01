#define F_CPU 16000000UL
#define STARTUP_DELAY 5000

#include "gpio.h"
#include "esc_driver.h"
#include "fs.h"
#include "fs_status_light.h"
#include "i2c.h"
#include <Arduino.h>

int main(void)
{

  _delay_ms(STARTUP_DELAY);
  gpio_setup();
}
