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
    selectedTimePart--;

    if (selectedTimePart == Timepart::YEAR) {
      selectedTimePart = Timepart::SECOND;
    }
  }

  void selectNext()
  {
    selectedTimePart++;

    if (selectedTimePart == Timepart::DAY) {
      selectedTimePart = Timepart::HOUR;
    }
  }
};

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
