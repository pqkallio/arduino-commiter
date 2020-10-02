#ifndef _COMMITTER_BUTTON_HPP
#define _COMMITTER_BUTTON_HPP

#include "../pins/pins.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define UP 4
#define SELECT 5
#define CANCEL 6

uint8_t get_button()
{
  int btn_val = analogRead(BTN_IN);

  if (btn_val > 1020) {
    return CANCEL;
  } else if (btn_val > 980) {
    return SELECT;
  } else if (btn_val > 900) {
    return RIGHT;
  } else if (btn_val > 670) {
    return UP;
  } else if (btn_val > 490) {
    return DOWN;
  } else if (btn_val > 0) {
    return LEFT;
  }

  return NONE;
}

#endif /* _COMMITTER_BUTTON_HPP */
