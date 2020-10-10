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
    analogWrite(LED_RED, R);
    analogWrite(LED_GREEN, G);
    analogWrite(LED_BLUE, B);
  }

  void setLedRGB(uint8_t red, uint8_t green, uint8_t blue)
  {
    R = red;
    G = green;
    B = blue;
  }

  void setLedColor(LedColor color)
  {
    switch (color) {
      case BLUE:
        setLedRGB(0, 0, (uint8_t)(b * 255));
        break;
      case GREEN:
        setLedRGB(0, (uint8_t)(b * 255), 0);
        break;
      case RED:
        setLedRGB((uint8_t)(b * 255), 0, 0);
        break;
      case YELLOW:
        setLedRGB((uint8_t)(b * 50), (uint8_t)(b * 255), 0);
        break;
      default:
        break;
    }

    updateLedColor();
  }

  void setLedBrightness(float brightness)
  {
    if (brightness < 0.0) {
      b = 0.0;
    } else if (brightness > 1.0) {
      b = 1.0;
    } else {
      b = brightness;
    }

    updateLedColor();
  }
};

#endif /* _COMMITTER_LED_HPP */
