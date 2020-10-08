#include <Arduino.h>
#include "lcd/lcd.hpp"
#include "lcd/glyphs.hpp"
#include "pins/pins.hpp"
#include "setup/setup.hpp"
#include "button/button.hpp"
#include "temperature/temperature.hpp"
#include "mode/mode.hpp"
#include "led/led.hpp"
#include "date/date.hpp"
#include "mode/idlemode.hpp"

IdleMode idleMode(&lcd);

uint8_t mode;

Date base_date{.day = 0, .month = 0, .year = 0, .time = 0};

void setup()
{
  setup_led();
  setup_lcd();

  lcd.clear();
  Serial.begin(9600);

  mode = IDLE;
}

void request_time(unsigned long current_time)
{

}

void loop()
{
  unsigned long current_time = millis();
  uint8_t btn = get_button();

  switch (mode) {
    case ENTER_TIME:
      request_time(current_time);
      break;

    default:
      idleMode.tick(btn, current_time);
      break;
  }

  delay(50);
}
