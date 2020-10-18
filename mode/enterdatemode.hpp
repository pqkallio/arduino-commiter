#ifndef _COMMITTER_ENTERDATEMODE_HPP
#define _COMMITTER_ENTERDATEMODE_HPP

#include "mode.hpp"
#include "enterchronosmode.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"
#include "../date/date.hpp"

static const uint8_t LEN_DATEPARTS = 3;

class EnterDateMode : public EnterChronosMode {
private:
  const Timepart TIMEPARTS[LEN_DATEPARTS] = {
    Timepart::DAY, Timepart::MONTH, Timepart::YEAR
  };

protected:
  void displayTime()
  {
    lcd->displayDate(baseDate);

    switch (selectedTimePart) {
      case Timepart::DAY:
        showSelectionAt(4, 0);
        break;
      case Timepart::MONTH:
        showSelectionAt(7, 0);
        break;
      case Timepart::YEAR:
        showSelectionAt(12, 0);
        break;
      default:
        lcd->noBlink();
        break;
    }
  }

public:
  EnterDateMode(
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    Date* baseDate
  ):
    EnterChronosMode(baseDate, lcd, led, buttonStrip, Timepart::DAY)
  {}

  void selectPrevious()
  {
    switch (selectedTimePart) {
      case Timepart::MONTH:
        selectedTimePart = Timepart::DAY;
        break;
      case Timepart::YEAR:
        selectedTimePart = Timepart::MONTH;
        break;
      default:
        selectedTimePart = Timepart::YEAR;
        break;
    }
  }

  void selectNext()
  {
    switch (selectedTimePart) {
      case Timepart::DAY:
        selectedTimePart = Timepart::MONTH;
        break;
      case Timepart::MONTH:
        selectedTimePart = Timepart::YEAR;
        break;
      default:
        selectedTimePart = Timepart::DAY;
        break;
    }
  }
};

#endif /* _COMMITTER_ENTERDATEMODE_HPP */
