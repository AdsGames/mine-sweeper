#include "Intro.h"

#include <asw/asw.h>

#include "utility/tools.h"

// Constructor
void Intro::init() {
  img_intro = asw::assets::loadTexture("assets/images/intro.png");
  img_title = asw::assets::loadTexture("assets/images/title.png");

  timer.start();
}

void Intro::update() {
  auto time = timer.getElapsedTime<std::chrono::milliseconds>();

  if (time > 3000 || asw::input::keyboard.anyPressed) {
    setNextState(ProgramState::STATE_MENU);
  }
}

// Draw to screen
void Intro::draw() {
  // A.D.S. Games Splash
  auto time = timer.getElapsedTime<std::chrono::milliseconds>();

  if (time < 1000) {
    asw::draw::sprite(img_intro, 0, 0);
  } else if (time < 2000) {
    asw::draw::sprite(img_title, 0, 0);
  }
}
