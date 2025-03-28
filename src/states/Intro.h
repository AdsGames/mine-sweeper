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
#include <memory>

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
  Timer timer;

  std::shared_ptr<asw::game::Sprite> intro;
  std::shared_ptr<asw::game::Sprite> title;
};

#endif  // INTRO_H
