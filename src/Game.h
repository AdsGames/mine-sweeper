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
  using State::State;

  // Override parent
  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{};

 private:
  // Bitmaps
  asw::Texture menuWin;
  asw::Texture menuLose;

  // Sounds
  asw::Sample explode;
  asw::Sample beep;

  // Minefield
  Minefield field;

  // Buttons
  Button menuYes;
  Button menuNo;

  // Game timer
  Timer gameTime;
  int lastBeepTime;

  // Mini state in game
  GameState gameState;

  // Sound enabled
  bool sound;
};

#endif  // GAME_H
