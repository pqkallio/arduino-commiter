#include <Arduino.h>
#include "lcd/lcd.hpp"
#include "pins/pins.hpp"
#include "setup/setup.hpp"
#include "button/button.hpp"

void setup()
{
  setup_led();
  setup_lcd();

  Serial.begin(9600);
}

void loop()
{
  int btn = get_button();

  String b = "None";

  switch (btn) {
    case LEFT:
      b = "Left";
      break;
    case RIGHT:
      b = "Right";
      break;
    case UP:
      b = "Up";
      break;
    case DOWN:
      b = "Down";
      break;
    case SELECT:
      b = "Select";
      break;
    case CANCEL:
      b = "Cancel";
      break;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(b);

  delay(500);
}
