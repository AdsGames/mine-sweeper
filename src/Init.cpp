#include "Init.h"

#include "./lib/aar/aar.h"
#include "globals.h"

// Construct state
void Init::init() {
  aar::util::init(128, 128, 4);

  aar::display::setTitle("Loading...");

  aar::display::setIcon("assets/images/icon.png");

  aar::display::setTitle("Minesweeper - A.D.S. Games");
}

// Update
void Init::update() {
  setNextState(StateEngine::STATE_INTRO);
}
