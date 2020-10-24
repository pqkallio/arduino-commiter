#ifndef _COMMITTER_ENTERTIMEMODE_HPP
#define _COMMITTER_ENTERTIMEMODE_HPP

#include "mode.hpp"
#include "enterchronosmode.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"
#include "../date/date.hpp"

static const uint8_t LEN_TIMEPARTS = 3;

class EnterTimeMode : public EnterChronosMode {
private:
  const Timepart TIMEPARTS[LEN_TIMEPARTS] = {
    Timepart::HOUR, Timepart::MINUTE, Timepart::SECOND
  };

protected:
  void displayTime()
  {
    lcd->displayTime(baseDate);

    switch (selectedTimePart) {
      case Timepart::HOUR:
        showSelectionAt(5, 0);
        break;
      case Timepart::MINUTE:
        showSelectionAt(8, 0);
        break;
      case Timepart::SECOND:
        showSelectionAt(11, 0);
        break;
      default:
        lcd->noBlink();
        break;
    }
  }

public:
  EnterTimeMode(
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    Date* baseDate
  ):
    EnterChronosMode(baseDate, lcd, led, buttonStrip, Timepart::HOUR)
  {}

  void selectPrevious()
  {
    switch (selectedTimePart) {
      case Timepart::MINUTE:
        selectedTimePart = Timepart::HOUR;
        break;
      case Timepart::SECOND:
        selectedTimePart = Timepart::MINUTE;
        break;
      default:
        selectedTimePart = Timepart::SECOND;
        break;
    }
  }

  void selectNext()
  {
    switch (selectedTimePart) {
      case Timepart::HOUR:
        selectedTimePart = Timepart::MINUTE;
        break;
      case Timepart::MINUTE:
        selectedTimePart = Timepart::SECOND;
        break;
      default:
        selectedTimePart = Timepart::HOUR;
        break;
    }
  }
};

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
