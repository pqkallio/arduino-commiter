#ifndef _COMMITTER_IDLEMODE_HPP
#define _COMMITTER_IDLEMODE_HPP

#include <LiquidCrystal.h>
#include "mode.hpp"
#include "../temperature/temperature.hpp"
#include "../lcd/glyphs.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"

#define TIME_FORMAT "%02d"

class IdleMode : public ModeInterface {
private:
  LiquidCrystal* lcd;
  RGBLed* led;
  ButtonStrip* buttonStrip;

  unsigned long temperatureInterval;
  unsigned long tempElapsed;
  unsigned long timeElapsed;
  unsigned long baseTimeInSeconds = 0;
  char secondDelimiter = ' ';

  /**
   * Update the first row of the display with presently evaluated temperature.
   */
  void handleTemperatureDisplay(unsigned long currentTime)
  {
    unsigned int newTempElapsed = currentTime % this->temperatureInterval;

    if (newTempElapsed < this->tempElapsed) {
      float celsius = measure_celsius_temperature();

      this->lcd->setCursor(0, 0);
      this->lcd->print("                ");
      this->lcd->setCursor(0, 0);
      this->lcd->write(byte(GLYPH_TEMPERATURE));
      this->lcd->print(" ");
      this->lcd->print(celsius);
    }

    this->tempElapsed = newTempElapsed;
  }

  /**
   * On the second row of the LCD display print
   *  - "HH:MM:SS" if on the first half of the second
   *  - "HH:MM SS" if on the second half of the second
   * I.e., "blink the second delimiter".
   */
  void handleTimeDisplay(unsigned long currentTime)
  {
    unsigned long newTimeElapsed = currentTime % 1000;

    if (newTimeElapsed < timeElapsed) {
      this->secondDelimiter = ':';
      unsigned long t = this->baseTimeInSeconds + currentTime / 1000;

      uint8_t seconds = t % 60;
      t /= 60;
      uint8_t minutes = t % 60;
      t /= 60;
      uint8_t hours = t % 24;

      char timepart[3];

      this->lcd->setCursor(0, 1);
      this->lcd->write(byte(GLYPH_CLOCK));
      this->lcd->print(" ");

      sprintf(timepart, TIME_FORMAT, hours);
      this->lcd->print(timepart);
      this->lcd->print(":");

      sprintf(timepart, TIME_FORMAT, minutes);
      this->lcd->print(timepart);
      this->lcd->print(this->secondDelimiter);

      sprintf(timepart, TIME_FORMAT, seconds);
      this->lcd->print(timepart);

    } else if (newTimeElapsed >= 500 && this->secondDelimiter != ' ') {
      this->secondDelimiter = ' ';
      this->lcd->setCursor(7, 1);
      this->lcd->print(this->secondDelimiter);
    }

    this->timeElapsed = newTimeElapsed;
  }

public:
  IdleMode(LiquidCrystal* lcd, RGBLed* led, ButtonStrip* buttonStrip, unsigned long temperatureInterval):
    lcd(lcd),
    led(led),
    buttonStrip(buttonStrip),
    temperatureInterval(temperatureInterval),
    tempElapsed(temperatureInterval - 1),
    timeElapsed(999)
  {}

  ModeInterface* tick(unsigned long currentTime)
  {
    this->handleTemperatureDisplay(currentTime);
    this->handleTimeDisplay(currentTime);

    return this;
  }

  void onEnter()
  {
    this->led->setLedColor(LedColor::GREEN);
  }
};

#endif /* _COMMITTER_IDLEMODE_HPP */
