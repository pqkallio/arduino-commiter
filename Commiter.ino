#include <Arduino.h>
#include "pins/pins.hpp"
#include "setup/setup.hpp"

void setup()
{
  setup_led();

  setup_lcd();

  Serial.begin(9600);
}

void loop()
{

  delay(100);
}
