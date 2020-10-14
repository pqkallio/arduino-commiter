#ifndef _COMMITTER_ENTERCHRONOSMODE_HPP
#define _COMMITTER_ENTERCHRONOSMODE_HPP

#include "mode.hpp"
#include "../date/date.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"

class EnterChronosMode: public ModeInterface {
protected:
  Timepart selectedTimePart;
  Date* baseDate;
  LCDDisplay* lcd;
  RGBLed* led;
  bool update;
  Selection selection;

  void unselect()
  {
    selectedTimePart = Timepart::NO_PART;
  }

  void increment()
  {
    switch (selectedTimePart) {
      case Timepart::DAY:
        baseDate->incrementDay();
        break;
      case Timepart::MONTH:
        baseDate->incrementMonth();
        break;
      case Timepart::YEAR:
        baseDate->incrementYear();
        break;
    }
  }

  void decrement()
  {
    switch (selectedTimePart) {
      case Timepart::DAY:
        baseDate->decrementDay();
        break;
      case Timepart::MONTH:
        baseDate->decrementMonth();
        break;
      case Timepart::YEAR:
        baseDate->decrementYear();
        break;
    }
  }

  virtual void selectNext() = 0;
  virtual void selectPrevious() = 0;
  virtual ModeInterface* handleButtonPress() = 0;

public:
  EnterChronosMode(
    Date* baseDate,
    LCDDisplay* lcd,
    RGBLed* led,
    Timepart selectedTimepart = Timepart::NO_PART
  ):
    baseDate(baseDate),
    selectedTimePart(selectedTimepart),
    lcd(lcd),
    led(led),
    selection(Selection::NONE_SELECTED)
  {};

  void onEnter()
  {
    lcd->clear();
    led->setLedColor(LedColor::BLUE);
  }

  ModeInterface* tick(unsigned long currentTime)
  {
    ModeInterface* nextMode = handleButtonPress();

    if (nextMode != this) {
      return nextMode;
    }

    if (update) {
      update = false;

      lcd->showConfirmationDialog(selection);
      lcd->displayDate(baseDate);
    }

    return this;
  }
};

#endif /* _COMMITTER_ENTERCHRONOSMODE_HPP */
