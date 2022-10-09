/*
 * Intro State
 * Allan Legemaate
 * 31/12/2016
 * Just some splashes
 */
#ifndef INTRO_H
#define INTRO_H

#include "./lib/aar/aar.h"
#include "State.h"
#include "utility/Timer.h"

class Intro : public State {
 public:
  explicit Intro(StateEngine& engine) : State(engine) {}

  // Override parent
  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override;

 private:
  // Images
  aar::Texture* img_intro;
  aar::Texture* img_title;

  Timer timer;
};

#endif  // INTRO_H
