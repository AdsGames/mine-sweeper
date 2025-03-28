#include "./Init.h"

#include <asw/asw.h>
#include "../globals.h"

// Construct state
void Init::init() {
  asw::display::setTitle("Loading...");

  asw::display::setIcon("assets/images/icon.png");

  asw::display::setTitle("Minesweeper - A.D.S. Games");
}

// Update
void Init::update(float _deltaTime) {
  sceneManager.setNextScene(States::Intro);
}
