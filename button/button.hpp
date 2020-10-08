#ifndef _COMMITTER_BUTTON_HPP
#define _COMMITTER_BUTTON_HPP

enum Button {
  NO_BUTTON,
  LEFT,
  RIGHT,
  DOWN,
  UP,
  SELECT,
  CANCEL
};

class ButtonStrip {
private:
  Button pressed;
  uint8_t input;

public:
  ButtonStrip(uint8_t input): input(input), pressed(Button::NO_BUTTON) {}

  Button getButton()
  {
    Button current = Button::NO_BUTTON;
    Button ret_val = Button::NO_BUTTON;

    int btn_val = analogRead(this->input);

    if (btn_val > 1020) {
      current = Button::CANCEL;
    } else if (btn_val > 980) {
      current = Button::SELECT;
    } else if (btn_val > 900) {
      current = Button::RIGHT;
    } else if (btn_val > 670) {
      current = Button::UP;
    } else if (btn_val > 490) {
      current = Button::DOWN;
    } else if (btn_val > 0) {
      current = Button::LEFT;
    }

    if (current == this->pressed) {
      ret_val = Button::NO_BUTTON;
    } else {
      ret_val = current;
    }

    this->pressed = current;

    return ret_val;
  }
};

#endif /* _COMMITTER_BUTTON_HPP */
