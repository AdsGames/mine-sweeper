#include "Init.h"

#include <asw/asw.h>
#include "globals.h"

// Construct state
void Init::init() {
  asw::core::init(128, 128, 4);

  asw::display::setTitle("Loading...");

  asw::display::setIcon("assets/images/icon.png");

  asw::display::setTitle("Minesweeper - A.D.S. Games");
}

// Update
void Init::update() {
  setNextState(ProgramState::STATE_INTRO);
}
