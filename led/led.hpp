#ifndef _COMMITTER_LED_HPP
#define _COMMITTER_LED_HPP

enum LedColor {
  BLUE,
  GREEN,
  RED,
  YELLOW
};

class RGBLed {
private:
  uint8_t R, G, B;
  float b = 1.0;

public:
  RGBLed(uint8_t redOutput, uint8_t greenOutput, uint8_t blueOutput)
  {
    pinMode(redOutput, OUTPUT);
    pinMode(greenOutput, OUTPUT);
    pinMode(blueOutput, OUTPUT);
  }

  void updateLedColor()
  {
    analogWrite(LED_RED, this->R);
    analogWrite(LED_GREEN, this->G);
    analogWrite(LED_BLUE, this->B);
  }

  void setLedRGB(uint8_t red, uint8_t green, uint8_t blue)
  {
    this->R = red;
    this->G = green;
    this->B = blue;
  }

  void setLedColor(LedColor color)
  {
    switch (color) {
      case BLUE:
        this->setLedRGB(0, 0, (uint8_t)(this->b * 255));
        break;
      case GREEN:
        this->setLedRGB(0, (uint8_t)(this->b * 255), 0);
        break;
      case RED:
        this->setLedRGB((uint8_t)(this->b * 255), 0, 0);
        break;
      case YELLOW:
        this->setLedRGB((uint8_t)(this->b * 50), (uint8_t)(this->b * 255), 0);
        break;
      default:
        break;
    }

    this->updateLedColor();
  }

  void setLedBrightness(float brightness)
  {
    if (brightness < 0.0) {
      this->b = 0.0;
    } else if (brightness > 1.0) {
      this->b = 1.0;
    } else {
      this->b = brightness;
    }

    this->updateLedColor();
  }
};

#endif /* _COMMITTER_LED_HPP */
