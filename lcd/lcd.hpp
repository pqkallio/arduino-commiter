#ifndef _COMMITTER_LCD_HPP
#define _COMMITTER_LCD_HPP

#include <LiquidCrystal.h>
#include "glyphs.hpp"
#include "../pins/pins.hpp"

class LCDDisplay {
private:
  LiquidCrystal lcd = LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

public:
  LCDDisplay()
  {
    this->lcd.begin(16, 2);
    this->lcd.clear();

    this->lcd.createChar(GLYPH_CHECK, check);
    this->lcd.createChar(GLYPH_CHECK_INVERTED, check_inverted);
    this->lcd.createChar(GLYPH_CROSS, cross);
    this->lcd.createChar(GLYPH_CROSS_INVERTED, cross_inverted);
    this->lcd.createChar(GLYPH_CLOCK, clock);
    this->lcd.createChar(GLYPH_TEMPERATURE, temperature);
    this->lcd.createChar(GLYPH_LEFT_BRACKET_INVERTED, left_bracket_inverted);
    this->lcd.createChar(GLYPH_RIGHT_BRACKET_INVERTED, right_bracket_inverted);
  }

  LiquidCrystal* getDisplay()
  {
    return &this->lcd;
  }
};

#endif /* _COMMITTER_LCD_HPP */
