#ifndef _COMMITTER_GLYPHS_HPP
#define _COMMITTER_GLYPHS_HPP

#define GLYPH_CHECK 0
#define GLYPH_CHECK_INVERTED 1
#define GLYPH_CROSS 2
#define GLYPH_CROSS_INVERTED 3
#define GLYPH_CLOCK 4
#define GLYPH_TEMPERATURE 5

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

#endif /* _COMMITTER_GLYPHS_HPP */
