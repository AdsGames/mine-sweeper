/*
 * Game state
 * Allan Legemaate
 * 30/12/2016
 * Main program here
 */

#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <asw/util/Timer.h>

#include "Minefield.h"
#include "ui/Button.h"

enum class GameState { GAME, WIN, LOSE };

class Game : public State {
 public:
  explicit Game(StateEngine& engine) : State(engine) {}

  // Override parent
  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override{};

 private:
  // Bitmaps
  asw::Texture menu_win, menu_lose;

  // Sounds
  asw::Sample explode, beep;

  // Minefield
  Minefield field;

  // Buttons
  Button menu_yes, menu_no;

  // Game timer
  Timer game_time;
  int last_beep_time;

  // Mini state in game
  GameState game_state;

  // Sound enabled
  bool sound;
};

#endif  // GAME_H
