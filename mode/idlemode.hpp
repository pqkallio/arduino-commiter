#ifndef _COMMITTER_IDLEMODE_HPP
#define _COMMITTER_IDLEMODE_HPP

#include "mode.hpp"
#include "../temperature/temperature.hpp"
#include "../lcd/glyphs.hpp"
#include "../lcd/lcd.hpp"
#include "../led/led.hpp"
#include "../button/button.hpp"


class IdleMode : public ModeInterface {
private:
  LCDDisplay* lcd;
  RGBLed* led;
  ButtonStrip* buttonStrip;
  TemperatureSensor* temperatureSensor;

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
    unsigned int newTempElapsed = currentTime % temperatureInterval;

    if (newTempElapsed < tempElapsed) {
      float celsius = temperatureSensor->measureCelsiusTemperature();

      lcd->showTemperature(celsius);
    }

    tempElapsed = newTempElapsed;
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

    unsigned long t = baseTimeInSeconds + currentTime / 1000;

    uint8_t seconds = t % 60;
    t /= 60;
    uint8_t minutes = t % 60;
    t /= 60;
    uint8_t hours = t % 24;

    if (newTimeElapsed < timeElapsed) {
      secondDelimiter = ':';
      lcd->showClock(hours, minutes, seconds, secondDelimiter);
    } else if (newTimeElapsed >= 500 && secondDelimiter != ' ') {
      secondDelimiter = ' ';
      lcd->showClock(hours, minutes, seconds, secondDelimiter);
    }

    timeElapsed = newTimeElapsed;
  }

public:
  IdleMode(
    LCDDisplay* lcd,
    RGBLed* led,
    ButtonStrip* buttonStrip,
    TemperatureSensor* temperatureSensor,
    unsigned long temperatureInterval
  ):
    lcd(lcd),
    led(led),
    buttonStrip(buttonStrip),
    temperatureSensor(temperatureSensor),
    temperatureInterval(temperatureInterval),
    tempElapsed(temperatureInterval - 1),
    timeElapsed(999)
  {}

  ModeInterface* tick(unsigned long currentTime)
  {
    handleTemperatureDisplay(currentTime);
    handleTimeDisplay(currentTime);

    return this;
  }

  void onEnter()
  {
    led->setLedColor(LedColor::GREEN);
  }
};

#endif /* _COMMITTER_IDLEMODE_HPP */
