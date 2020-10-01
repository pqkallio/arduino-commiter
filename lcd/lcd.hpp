#ifndef _COMMITER_LCD_H
#define _COMMITER_LCD_H

#include <LiquidCrystal.h>
#include "../pins/pins.hpp"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#endif /* _COMMITER_LCD_H */
