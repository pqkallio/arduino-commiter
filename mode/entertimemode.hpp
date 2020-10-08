#ifndef _COMMITTER_ENTERTIMEMODE_HPP
#define _COMMITTER_ENTERTIMEMODE_HPP

#include "mode.hpp"
#include "idlemode.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"
#include "../date/date.hpp"

class EnterTimeMode : public ModeInterface {
private:
  LCDDisplay* lcd;
  RGBLed* led;
  ButtonStrip* buttonStrip;
  Date* baseDate;
  IdleMode* idleMode;
  Selection selection;

public:
  EnterTimeMode(
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    Date* baseDate,
    IdleMode* idleMode
  ):
    lcd(lcd),
    led(led),
    buttonStrip(buttonStrip),
    baseDate(baseDate),
    idleMode(idleMode),
    selection(Selection::NONE_SELECTED)
  {}
};

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
