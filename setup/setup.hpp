#ifndef _COMMITTER_SETUP_HPP
#define _COMMITTER_SETUP_HPP

#include "../pins/pins.hpp"
#include "../lcd/lcd.hpp"
#include "../lcd/glyphs.hpp"
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

  lcd.createChar(GLYPH_CHECK, check);
  lcd.createChar(GLYPH_CHECK_INVERTED, check_inverted);
  lcd.createChar(GLYPH_CROSS, cross);
  lcd.createChar(GLYPH_CROSS_INVERTED, cross_inverted);
  lcd.createChar(GLYPH_CLOCK, clock);
  lcd.createChar(GLYPH_TEMPERATURE, temperature);

  lcd.setCursor(0, 0);
  lcd.print("Ready for");
  lcd.setCursor(0, 1);
  lcd.print("commit magix");
}

#endif /* _COMMITTER_SETUP_HPP */
