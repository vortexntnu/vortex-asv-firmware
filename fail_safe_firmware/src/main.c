#include "gpio.h"
#include "esc_driver.h"
#include "fs.h"
#include "fs_status_light.h"
#include "i2c.h"

void setup()
{
  delay(5000);

  GPIO_setup();

  FS_Status_Light::set_rgby(LOW, LOW, LOW, LOW);
  FS_Status_Light::test_leds();
  delay(1000);
  FS_Status_Light::test_24v_status();
  delay(2000);

  ESC_Driver::setup();

  Serial.println(F("Smoke break, brb..."));
  delay(STARTUP_DELAY);

  Serial.println(F("Setting up I2C communication 'That thing that embedded people always rant about but no one actually cares...'"));
  I2C::setup();
}

void loop()
{
  digitalWrite(LED_ARMED_STATUS, IS_ARMED ? HIGH : LOW);

  allSystemsGo = true;

  fs::test_fs_trigger(OtA_KS, LED_OtA_KS);
  fs::test_fs_trigger(BUTTON_KS, LED_HW_KS);
  fs::test_fs_trigger(OM, LED_RX_TO);
  // fs::test_sw_ks(???);

  if (fsLocked)
  {
    digitalWrite(LED_FS_LOCKED_STATUS, HIGH);

    if (IS_ARMED)
    {
      allSystemsGo = false;
    }
    else if (allSystemsGo)
    {
      fsLocked = false;
      digitalWrite(LED_FS_LOCKED_STATUS, LOW);
    }
    else
    {
    }
  }
  else
  {
    if (IS_ARMED)
    {
      if (allSystemsGo)
      {
        fs::set_main_output(HIGH);
      }
      else
      {
        fs::set_main_output(LOW);
      }
    }
    else
    {
      fs::set_main_output(LOW);
    }
  }

  ESC_Driver::run();
}
