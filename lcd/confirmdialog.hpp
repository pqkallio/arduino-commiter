#ifndef _COMMITTER_LCD_CONFIRMATIONDIALOG_HPP
#define _COMMITTER_LCD_CONFIRMATIONDIALOG_HPP

#include "lcd.hpp"
#include "glyphs.hpp"

#define NONE 0;
#define CONFIRM 1;
#define CANCEL 2;

void print_selected(uint8_t glyph)
{
  lcd.write(GLYPH_LEFT_BRACKET_INVERTED);
  lcd.write(glyph);
  lcd.write(GLYPH_RIGHT_BRACKET_INVERTED);
}

void print_unselected(uint8_t glyph)
{
  lcd.print("[");
  lcd.write(glyph);
  lcd.print("]");
}

void show_confirmation_dialog(uint8_t selected)
{
  lcd.setCursor(0, 1);
  lcd.print("   ");

  if (selected == CONFIRM) {
    print_selected(GLYPH_CHECK_INVERTED);
  } else {
    print_unselected(GLYPH_CHECK);
  }

  lcd.print("    ");

  if (selected == CANCEL) {
    print_selected(GLYPH_CROSS_INVERTED);
  } else {
    print_unselected(GLYPH_CROSS);
  }

  lcd.print("   ");
}

#endif /* _COMMITTER_LCD_CONFIRMATIONDIALOG_HPP */
