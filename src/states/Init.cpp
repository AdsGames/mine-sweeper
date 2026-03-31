#include "./Init.h"

#include <asw/asw.h>
#include "../globals.h"

// Construct state
void Init::init() {
  asw::display::set_title("Loading...");

  asw::display::set_icon("assets/images/icon.png");

  asw::display::set_title("Minesweeper - A.D.S. Games");
}

// Update
void Init::update(float _dt) {
  manager.set_next_scene(States::Intro);
}
