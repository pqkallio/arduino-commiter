#ifndef _COMMITER_SETUP_H
#define _COMMITER_SETUP_H

#include "../pins/pins.hpp"
#include "../lcd/lcd.hpp"

void setup_led()
{
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_RED, 0);
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

#endif /* _COMMITER_SETUP_H */
