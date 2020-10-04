#ifndef _COMMITTER_SETUP_HPP
#define _COMMITTER_SETUP_HPP

#include "../pins/pins.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"

void setup_led()
{
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  set_led_color(GREEN);
}

void setup_lcd()
{
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Ready for");
  lcd.setCursor(0, 1);
  lcd.print("commit magix");
}

#endif /* _COMMITTER_SETUP_HPP */
