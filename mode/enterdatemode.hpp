#ifndef _COMMITTER_ENTERTIMEMODE_HPP
#define _COMMITTER_ENTERTIMEMODE_HPP

#include "mode.hpp"
#include "enterchronosmode.hpp"
#include "idlemode.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"
#include "../date/date.hpp"

enum EnterTimePhase {
  ENTER_TIME,
  CONFIRM_TIME
};

static const uint8_t LEN_DATEPARTS = 3;

class EnterDateMode : public EnterChronosMode {
private:
  const Timepart TIMEPARTS[LEN_DATEPARTS] = {
    Timepart::DAY, Timepart::MONTH, Timepart::YEAR
  };
  ButtonStrip* buttonStrip;
  IdleMode* idleMode;
  EnterTimePhase phase;
  bool update;

  ModeInterface* handleEnterDateButtonPress(Button btn)
  {
    switch (btn) {
      case Button::RIGHT:
        selectNext();
        update = true;

        break;

      case Button::LEFT:
        selectPrevious();
        update = true;

        break;

      case Button::UP:
        increment();
        update = true;

        break;

      case Button::DOWN:
        decrement();
        update = true;

        break;

      case Button::SELECT:
        selection = Selection::CONFIRM_SELECTED;
        phase = EnterTimePhase::CONFIRM_TIME;
        unselect();
        update = true;

        break;
    }

    return this;
  }

  ModeInterface* handleConfirmDateButtonPress(Button btn)
  {
    switch (btn) {
      case Button::SELECT:
        return idleMode;

      case Button::CANCEL:
        selection = Selection::NONE_SELECTED;
        phase = EnterTimePhase::ENTER_TIME;
        selectNext();
        update = true;

        break;

      case Button::LEFT:
        selection = Selection::CONFIRM_SELECTED;
        update = true;

        break;

      case Button::RIGHT:
        selection = Selection::CANCEL_SELECTED;
        update = true;

        break;
    }

    return this;
  }

  ModeInterface* handleButtonPress()
  {
    Button btn = buttonStrip->getButton();

    switch (phase) {
      case EnterTimePhase::ENTER_TIME:
        return handleEnterDateButtonPress(btn);

      case EnterTimePhase::CONFIRM_TIME:
        return handleConfirmDateButtonPress(btn);
    }

    return this;
  }

public:
  EnterDateMode(
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    Date* baseDate,
    IdleMode* idleMode
  ):
    EnterChronosMode(baseDate, lcd, led, Timepart::DAY),
    buttonStrip(buttonStrip),
    idleMode(idleMode),
    phase(EnterTimePhase::ENTER_TIME),
    update(true)
  {}

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

      lcd->displayDate(baseDate);
      lcd->showConfirmationDialog(selection);

      int8_t selectedCol = -1;

      switch (selectedTimePart) {
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
        lcd->setCursor(selectedCol, 0);
        lcd->blink();
      } else {
        lcd->noBlink();
      }
    }

    return this;
  }

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

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
