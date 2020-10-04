#ifndef _COMMITTER_LCD_HPP
#define _COMMITTER_LCD_HPP

#include <LiquidCrystal.h>
#include "../pins/pins.hpp"
#include "glyphs.hpp"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#endif /* _COMMITTER_LCD_HPP */
