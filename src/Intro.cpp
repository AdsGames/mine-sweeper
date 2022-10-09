#include "Intro.h"

#include <asw/util/KeyListener.h>

#include "utility/tools.h"

// Constructor
void Intro::init() {
  img_intro = asw::load::texture("assets/images/intro.png");
  img_title = asw::load::texture("assets/images/title.png");

  timer.Start();
}

void Intro::update() {
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time > 3000 || KeyListener::anyKeyPressed) {
    setNextState(ProgramState::STATE_MENU);
  }
}

// Draw to screen
void Intro::draw() {
  // A.D.S. Games Splash
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time < 1000) {
    asw::draw::sprite(img_intro, 0, 0);
  } else if (time < 2000) {
    asw::draw::sprite(img_title, 0, 0);
  }
}
