#ifndef _COMMITTER_ENTERTIMEMODE_HPP
#define _COMMITTER_ENTERTIMEMODE_HPP

#include "mode.hpp"
#include "idlemode.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"
#include "../date/date.hpp"

enum EnterTimePhase {
  ENTER_TIME,
  CONFIRM_TIME
};

class EnterTimeMode : public ModeInterface {
private:
  LCDDisplay* lcd;
  RGBLed* led;
  ButtonStrip* buttonStrip;
  Date* baseDate;
  IdleMode* idleMode;
  Selection selection;
  EnterTimePhase phase;
  bool update;

  ModeInterface* handleEnterTimeButtonPress(Button btn)
  {
    switch (btn) {
      case Button::RIGHT:
        baseDate->selectNext();
        update = true;

        break;

      case Button::LEFT:
        baseDate->selectPrevious();
        update = true;

        break;

      case Button::UP:
        baseDate->increment();
        update = true;

        break;

      case Button::DOWN:
        baseDate->decrement();
        update = true;

        break;

      case Button::SELECT:
        selection = Selection::CONFIRM_SELECTED;
        phase = EnterTimePhase::CONFIRM_TIME;
        baseDate->unselect();
        update = true;

        break;
    }

    return this;
  }

  ModeInterface* handleConfirmTimeButtonPress(Button btn)
  {
    switch (btn) {
      case Button::SELECT:
        return idleMode;

      case Button::CANCEL:
        selection = Selection::NONE_SELECTED;
        phase = EnterTimePhase::ENTER_TIME;
        baseDate->selectNext();
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
        return handleEnterTimeButtonPress(btn);

      case EnterTimePhase::CONFIRM_TIME:
        return handleConfirmTimeButtonPress(btn);
    }

    return this;
  }

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
    selection(Selection::NONE_SELECTED),
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

      lcd->showConfirmationDialog(selection);
      lcd->displayDate(baseDate);
    }

    return this;
  }
};

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
