#ifndef _COMMITTER_LED_HPP
#define _COMMITTER_LED_HPP

#include "../pins/pins.hpp"

#define BLUE 0
#define GREEN 1
#define RED 2
#define YELLOW 3

uint8_t R, G, B;
float b = 1.0;

void update_led_color()
{
  analogWrite(LED_RED, R);
  analogWrite(LED_GREEN, G);
  analogWrite(LED_BLUE, B);
}

void set_led_RGB(uint8_t red, uint8_t green, uint8_t blue)
{
  R = red;
  G = green;
  B = blue;
}

void set_led_color(uint8_t color)
{
  switch (color) {
    case BLUE:
      set_led_RGB(0, 0, (uint8_t)(b * 255));
      break;
    case GREEN:
      set_led_RGB(0, (uint8_t)(b * 255), 0);
      break;
    case RED:
      set_led_RGB((uint8_t)(b * 255), 0, 0);
      break;
    case YELLOW:
      set_led_RGB((uint8_t)(b * 50), (uint8_t)(b * 255), 0);
      break;
    default:
      break;
  }

  update_led_color();
}

void set_led_brightness(float brightness)
{
  if (brightness < 0.0) {
    b = 0.0;
  } else if (brightness > 1.0) {
    b = 1.0;
  } else {
    b = brightness;
  }

  update_led_color();
}

#endif /* _COMMITTER_LED_HPP */
