#ifndef _COMMITTER_LCD_HPP
#define _COMMITTER_LCD_HPP

#include <LiquidCrystal.h>
#include "glyphs.hpp"
#include "../pins/pins.hpp"
#include "../date/date.hpp"

#define TIME_FORMAT "%02d"

enum Selection {
  NONE_SELECTED,
  CONFIRM_SELECTED,
  CANCEL_SELECTED
};

class LCDDisplay {
private:
  const uint8_t N_ROWS = 2;
  const uint8_t N_COLS = 16;

  LiquidCrystal lcd = LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

  void printSelected(Glyph glyph)
  {
    lcd.write(Glyph::LEFT_BRACKET_INVERTED);
    lcd.write(glyph);
    lcd.write(Glyph::RIGHT_BRACKET_INVERTED);
  }

  void printUnselected(Glyph glyph)
  {
    lcd.print("[");
    lcd.write(glyph);
    lcd.print("]");
  }

public:
  LCDDisplay()
  {
    this->lcd.begin(LCDDisplay::N_COLS, LCDDisplay::N_ROWS);
    this->lcd.clear();

    this->lcd.createChar(Glyph::CHECK, check);
    this->lcd.createChar(Glyph::CHECK_INVERTED, check_inverted);
    this->lcd.createChar(Glyph::CROSS, cross);
    this->lcd.createChar(Glyph::CROSS_INVERTED, cross_inverted);
    this->lcd.createChar(Glyph::CLOCK, clock);
    this->lcd.createChar(Glyph::TEMPERATURE, temperature);
    this->lcd.createChar(Glyph::LEFT_BRACKET_INVERTED, left_bracket_inverted);
    this->lcd.createChar(Glyph::RIGHT_BRACKET_INVERTED, right_bracket_inverted);
  }

  LiquidCrystal* getDisplay()
  {
    return &this->lcd;
  }

  void clear(int8_t row = -1)
  {
    if (row < 0) {
      this->lcd.clear();
    } else if (row < LCDDisplay::N_ROWS) {
      this->lcd.setCursor(0, row);
      this->lcd.print("                ");
    }
  }

  void showConfirmationDialog(Selection selected = Selection::NONE_SELECTED)
  {
    lcd.setCursor(0, 1);
    lcd.print("   ");

    if (selected == Selection::CONFIRM_SELECTED) {
      this->printSelected(Glyph::CHECK_INVERTED);
    } else {
      this->printUnselected(Glyph::CHECK);
    }

    lcd.print("    ");

    if (selected == Selection::CANCEL_SELECTED) {
      this->printSelected(Glyph::CROSS_INVERTED);
    } else {
      this->printUnselected(Glyph::CROSS);
    }

    lcd.print("   ");
  }

  void showTemperature(float temperature)
  {
    this->clear(0);
    this->lcd.setCursor(0, 0);
    this->lcd.write(byte(Glyph::TEMPERATURE));
    this->lcd.print(" ");
    this->lcd.print(temperature);
  }

  void showClock(uint8_t hours, uint8_t minutes, uint8_t seconds, char secondDelimiter)
  {
    char timepart[3];

    this->lcd.setCursor(0, 1);
    this->lcd.write(byte(Glyph::CLOCK));
    this->lcd.print(" ");

    sprintf(timepart, TIME_FORMAT, hours);
    this->lcd.print(timepart);
    this->lcd.print(":");

    sprintf(timepart, TIME_FORMAT, minutes);
    this->lcd.print(timepart);
    this->lcd.print(secondDelimiter);

    sprintf(timepart, TIME_FORMAT, seconds);
    this->lcd.print(timepart);
  }

  void displayDate(Date* date)
  {
    int8_t selectedCol = -1;
    char timepart[3];

    this->clear(0);
    this->lcd.setCursor(0, 0);
    lcd.print("   ");

    sprintf(timepart, TIME_FORMAT, date->getDay());
    this->lcd.print(timepart);
    this->lcd.print(".");

    sprintf(timepart, TIME_FORMAT, date->getMonth());
    this->lcd.print(timepart);
    this->lcd.print(".");

    sprintf(timepart, TIME_FORMAT, date->getYear());
    this->lcd.print(timepart);

    switch (date->getSelectedTimepart()) {
      case Timepart::DAY:
        selectedCol = 4;
        break;
      case Timepart::MONTH:
        selectedCol = 7;
        break;
      case Timepart::YEAR:
        selectedCol = 12;
        break;
    }

    if (selectedCol > -1) {
      this->lcd.setCursor(selectedCol, 0);
      this->lcd.blink();
    } else {
      this->lcd.noBlink();
    }
  }
};

#endif /* _COMMITTER_LCD_HPP */
