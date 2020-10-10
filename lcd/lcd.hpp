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

  void printSelection(Glyph glyph)
  {
    lcd.print("[");
    lcd.write(glyph);
    lcd.print("]");
  }

public:
  LCDDisplay()
  {
    lcd.begin(LCDDisplay::N_COLS, LCDDisplay::N_ROWS);
    lcd.clear();

    lcd.createChar(Glyph::CHECK, check);
    lcd.createChar(Glyph::CHECK_INVERTED, check_inverted);
    lcd.createChar(Glyph::CROSS, cross);
    lcd.createChar(Glyph::CROSS_INVERTED, cross_inverted);
    lcd.createChar(Glyph::CLOCK, clock);
    lcd.createChar(Glyph::TEMPERATURE, temperature);
  }

  LiquidCrystal* getDisplay()
  {
    return &lcd;
  }

  void clear(int8_t row = -1)
  {
    if (row < 0) {
      lcd.clear();
    } else if (row < LCDDisplay::N_ROWS) {
      lcd.setCursor(0, row);
      lcd.print("                ");
    }
  }

  void showConfirmationDialog(Selection selected = Selection::NONE_SELECTED)
  {
    lcd.setCursor(0, 1);
    lcd.print("   ");

    Glyph check = selected == Selection::CONFIRM_SELECTED ? Glyph::CHECK_INVERTED : Glyph::CHECK;
    Glyph cross = selected == Selection::CANCEL_SELECTED ? Glyph::CROSS_INVERTED : Glyph::CROSS;

    printSelection(check);
    lcd.print("    ");
    printSelection(cross);

    lcd.print("   ");
  }

  void showTemperature(float temperature)
  {
    clear(0);
    lcd.setCursor(0, 0);
    lcd.write(byte(Glyph::TEMPERATURE));
    lcd.print(" ");
    lcd.print(temperature);
  }

  void showClock(uint8_t hours, uint8_t minutes, uint8_t seconds, char secondDelimiter)
  {
    char timepart[3];

    lcd.setCursor(0, 1);
    lcd.write(byte(Glyph::CLOCK));
    lcd.print(" ");

    sprintf(timepart, TIME_FORMAT, hours);
    lcd.print(timepart);
    lcd.print(":");

    sprintf(timepart, TIME_FORMAT, minutes);
    lcd.print(timepart);
    lcd.print(secondDelimiter);

    sprintf(timepart, TIME_FORMAT, seconds);
    lcd.print(timepart);
  }

  void displayDate(Date* date)
  {
    int8_t selectedCol = -1;
    char timepart[3];

    clear(0);
    lcd.setCursor(0, 0);
    lcd.print("   ");

    sprintf(timepart, TIME_FORMAT, date->getDay());
    lcd.print(timepart);
    lcd.print(".");

    sprintf(timepart, TIME_FORMAT, date->getMonth());
    lcd.print(timepart);
    lcd.print(".");

    sprintf(timepart, TIME_FORMAT, date->getYear());
    lcd.print(timepart);

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
      lcd.setCursor(selectedCol, 0);
      lcd.blink();
    } else {
      lcd.noBlink();
    }
  }
};

#endif /* _COMMITTER_LCD_HPP */
