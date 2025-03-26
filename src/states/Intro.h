/*
 * Intro State
 * Allan Legemaate
 * 31/12/2016
 * Just some splashes
 */
#ifndef INTRO_H
#define INTRO_H

#include <asw/asw.h>
#include <asw/util/Timer.h>

#include "State.h"

class Intro : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override;
  void cleanup() override {};

 private:
  // Images
  asw::Texture img_intro;
  asw::Texture img_title;

  Timer timer;
};

#endif  // INTRO_H
