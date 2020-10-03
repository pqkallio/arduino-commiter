#include <Arduino.h>
#include "lcd/lcd.hpp"
#include "pins/pins.hpp"
#include "setup/setup.hpp"
#include "button/button.hpp"
#include "temperature/temperature.hpp"

#define TEMPERATURE_INTERVAL_MS 60000;

unsigned long temp_elapsed;
unsigned time_elapsed;
char upper_row[16];

void setup()
{
  setup_led();
  setup_lcd();

  temp_elapsed = TEMPERATURE_INTERVAL_MS - 1;

  Serial.begin(9600);
}

void loop()
{
  unsigned int current_time = millis();
  unsigned int new_temp_elapsed = current_time % TEMPERATURE_INTERVAL_MS;

  if (new_temp_elapsed < temp_elapsed) {
    float celsius = measure_celsius_temperature();

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(celsius);
  }

  temp_elapsed = new_temp_elapsed;

  delay(100);
}
