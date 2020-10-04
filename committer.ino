#include <Arduino.h>
#include "lcd/lcd.hpp"
#include "lcd/glyphs.hpp"
#include "pins/pins.hpp"
#include "setup/setup.hpp"
#include "button/button.hpp"
#include "temperature/temperature.hpp"
#include "mode/mode.hpp"
#include "led/led.hpp"
#include "date/date.hpp"

#define TEMPERATURE_INTERVAL_MS 30000
#define TIME_FORMAT "%02d"

unsigned long temp_elapsed;
unsigned long time_elapsed;
unsigned long base_time_in_seconds = 0;
char second_delimiter = ' ';
char timepart[3];
uint8_t mode;

Date base_date{.day = 0, .month = 0, .year = 0, .time = 0};

void setup()
{
  setup_led();
  setup_lcd();

  temp_elapsed = TEMPERATURE_INTERVAL_MS - 1;
  time_elapsed = 999;

  lcd.clear();
  Serial.begin(9600);

  mode = IDLE;
}

/**
 * Update the first row of the display with presently evaluated temperature.
 */
void handle_temperature_display(unsigned long current_time)
{
  unsigned int new_temp_elapsed = current_time % TEMPERATURE_INTERVAL_MS;

  if (new_temp_elapsed < temp_elapsed) {
    float celsius = measure_celsius_temperature();

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.write(byte(GLYPH_TEMPERATURE));
    lcd.print(" ");
    lcd.print(celsius);
  }

  temp_elapsed = new_temp_elapsed;
}

/**
 * On the second row of the LCD display print
 *  - "HH:MM:SS" if on the first half of the second
 *  - "HH:MM SS" if on the second half of the second
 * I.e., "blink the second delimiter".
 */
void handle_time_display(unsigned long current_time)
{
  unsigned long new_time_elapsed = current_time % 1000;

  if (new_time_elapsed < time_elapsed) {
    second_delimiter = ':';
    unsigned long t = base_time_in_seconds + current_time / 1000;

    uint8_t seconds = t % 60;
    t /= 60;
    uint8_t minutes = t % 60;
    t /= 60;
    uint8_t hours = t % 24;

    lcd.setCursor(0, 1);
    lcd.write(byte(GLYPH_CLOCK));
    lcd.print(" ");

    sprintf(timepart, TIME_FORMAT, hours);
    lcd.print(timepart);
    lcd.print(":");

    sprintf(timepart, TIME_FORMAT, minutes);
    lcd.print(timepart);
    lcd.print(second_delimiter);

    sprintf(timepart, TIME_FORMAT, seconds);
    lcd.print(timepart);
  } else if (new_time_elapsed >= 500 && second_delimiter != ' ') {
    second_delimiter = ' ';
    lcd.setCursor(7, 1);
    lcd.print(second_delimiter);
  }

  time_elapsed = new_time_elapsed;
}

void idle(unsigned long current_time)
{
  handle_temperature_display(current_time);
  handle_time_display(current_time);
}

void loop()
{
  unsigned long current_time = millis();
/*
  if (!date_set(&base_date)) {
    mode = ENTER_TIME;
    set_led_color(YELLOW);
  }
 */
  switch (mode) {
    case ENTER_TIME:

      break;

    default:
      idle(current_time);
  }

  delay(50);
}
