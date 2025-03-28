/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include <asw/asw.h>

#include "../globals.h"
#include "./State.h"

class Init : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override {};
  void cleanup() override {};
};

#endif  // INIT_H
