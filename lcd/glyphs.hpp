#ifndef _COMMITTER_GLYPHS_HPP
#define _COMMITTER_GLYPHS_HPP

enum Glyph {
  CHECK,
  CHECK_INVERTED,
  CROSS,
  CROSS_INVERTED,
  CLOCK,
  TEMPERATURE,
  LEFT_BRACKET_INVERTED,
  RIGHT_BRACKET_INVERTED,
};

byte check[] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

byte check_inverted[] = {
  B11111,
  B11110,
  B11100,
  B01001,
  B00011,
  B10111,
  B11111,
  B11111,
};

byte cross[] = {
  B00000,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B00000,
  B00000
};

byte cross_inverted[] = {
  B11111,
  B01110,
  B10101,
  B11011,
  B10101,
  B01110,
  B11111,
  B11111
};

byte clock[] = {
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000,
  B00000
};

byte temperature[] = {
  B01110,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

byte left_bracket_inverted[] = {
  B10001,
  B10111,
  B10111,
  B10111,
  B10111,
  B10111,
  B10001,
  B11111
};

byte right_bracket_inverted[] = {
  B10001,
  B11101,
  B11101,
  B11101,
  B11101,
  B11101,
  B10001,
  B11111
};

#endif /* _COMMITTER_GLYPHS_HPP */
