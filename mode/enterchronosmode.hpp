#ifndef _COMMITTER_ENTERCHRONOSMODE_HPP
#define _COMMITTER_ENTERCHRONOSMODE_HPP

#include "mode.hpp"
#include "../date/date.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"

enum EnterTimePhase {
  ENTER_TIME,
  CONFIRM_TIME
};

class EnterChronosMode: public ModeInterface {
private:
  RGBLed* led;
  bool update;
  Selection selection;
  EnterTimePhase phase;
  ButtonStrip* buttonStrip;
  ModeInterface* previousMode;
  ModeInterface* nextMode;

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
        incrementSelectedTimepart();
        update = true;

        break;

      case Button::DOWN:
        decrementSelectedTimepart();
        update = true;

        break;

      case Button::SELECT:
        selection = Selection::CONFIRM_SELECTED;
        phase = EnterTimePhase::CONFIRM_TIME;
        unselect();
        update = true;

        break;

      case Button::CANCEL:
        if (previousMode) {
          return previousMode;
        }

        break;
    }

    return this;
  }

  ModeInterface* handleConfirmDateButtonPress(Button btn)
  {
    switch (btn) {
      case Button::SELECT:
        if (nextMode != NULL) {
          return nextMode;
        }

        break;

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

protected:
  Timepart selectedTimePart;
  Date* baseDate;
  LCDDisplay* lcd;

  void unselect()
  {
    selectedTimePart = Timepart::NO_PART;
  }

  void incrementSelectedTimepart()
  {
    baseDate->increment(selectedTimePart);
  }

  void decrementSelectedTimepart()
  {
    baseDate->decrement(selectedTimePart);
  }

  void showSelectionAt(uint8_t col, uint8_t row)
  {
    lcd->setCursor(col, row);
    lcd->blink();
  }

  virtual void selectNext() = 0;
  virtual void selectPrevious() = 0;
  virtual void displayTime() = 0;

public:
  EnterChronosMode(
    Date* baseDate,
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    Timepart selectedTimepart = Timepart::NO_PART
  ):
    baseDate(baseDate),
    selectedTimePart(selectedTimepart),
    lcd(lcd),
    led(led),
    buttonStrip(buttonStrip),
    nextMode(NULL),
    previousMode(NULL),
    selection(Selection::NONE_SELECTED),
    phase(EnterTimePhase::ENTER_TIME),
    update(true)
  {};

  void setNextMode(ModeInterface* mode) {
    nextMode = mode;
  }

  void setPreviousMode(ModeInterface* mode) {
    previousMode = mode;
  }

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
      displayTime();
    }

    return this;
  }
};

#endif /* _COMMITTER_ENTERCHRONOSMODE_HPP */
