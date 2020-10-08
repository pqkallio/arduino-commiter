#ifndef _COMMITTER_MODE_HPP
#define _COMMITTER_MODE_HPP

#define ENTER_TIME 0
#define IDLE 1

/**
 * An interface to be implemented by all specific execution modes.
 */
class ModeInterface {
public:
  /**
   * Called when the mode is entered.
   */
  virtual void onEnter() = 0;

  /**
   * Called in each loop.
   * Must return {this} or the following mode.
   */
  virtual ModeInterface* tick(uint8_t button, unsigned long currentTime) = 0;
};

#endif /* _COMMITTER_MODE_HPP */
