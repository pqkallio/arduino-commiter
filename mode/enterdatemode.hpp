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
    selectedTimePart--;

    if (selectedTimePart == Timepart::MINUTE) {
      selectedTimePart = Timepart::YEAR;
    }
  }

  void selectNext()
  {
    selectedTimePart++;

    if (selectedTimePart == Timepart::HOUR) {
      selectedTimePart = Timepart::DAY;
    }
  }
};

#endif /* _COMMITTER_ENTERDATEMODE_HPP */
