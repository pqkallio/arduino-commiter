#ifndef _COMMITTER_ENTERTIMEMODE_HPP
#define _COMMITTER_ENTERTIMEMODE_HPP

#include <LiquidCrystal.h>
#include "mode.hpp"
#include "idlemode.hpp"

class EnterTimeMode : public ModeInterface {
private:
  LiquidCrystal* lcd;
  IdleMode* idleMode;
};

#endif /* _COMMITTER_ENTERTIMEMODE_HPP */
