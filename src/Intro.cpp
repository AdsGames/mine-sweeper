#include "Intro.h"

#include "utility/KeyListener.h"
#include "utility/tools.h"

// Constructor
void Intro::init() {
  img_intro = aar::load::bitmap("assets/images/intro.png");
  img_title = aar::load::bitmap("assets/images/title.png");

  timer.Start();
}

// Destructor
void Intro::cleanup() {
  aar::load::destroyTexture(img_intro);
  aar::load::destroyTexture(img_title);
}

void Intro::update() {
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time > 3000 || KeyListener::anyKeyPressed) {
    setNextState(StateEngine::STATE_MENU);
  }
}

// Draw to screen
void Intro::draw() {
  // A.D.S. Games Splash
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time < 1000) {
    aar::draw::sprite(img_intro, 0, 0);
  } else if (time < 2000) {
    aar::draw::sprite(img_title, 0, 0);
  }
}
