#ifndef _COMMITTER_BUTTON_HPP
#define _COMMITTER_BUTTON_HPP

#include "../pins/pins.hpp"

#define NO_BUTTON 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define UP 4
#define SELECT 5
#define CANCEL 6

uint8_t previous = NO_BUTTON;

uint8_t get_button()
{
  uint8_t current = NO_BUTTON;
  uint8_t ret_val = NO_BUTTON;

  int btn_val = analogRead(BTN_IN);

  if (btn_val > 1020) {
    current = CANCEL;
  } else if (btn_val > 980) {
    current = SELECT;
  } else if (btn_val > 900) {
    current = RIGHT;
  } else if (btn_val > 670) {
    current = UP;
  } else if (btn_val > 490) {
    current = DOWN;
  } else if (btn_val > 0) {
    current = LEFT;
  }

  if (current == previous) {
    ret_val = NO_BUTTON;
  } else {
    ret_val = current;
  }

  previous = current;

  return ret_val;
}

#endif /* _COMMITTER_BUTTON_HPP */
