/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include "State.h"
#include "globals.h"

class Init : public State {
 public:
  explicit Init(StateEngine& engine) : State(engine) {}

  // Override parent
  virtual void init() override;
  virtual void update() override;
  virtual void draw() override{};
  virtual void cleanup() override{};

  // Defaults graphics mode
  static int set_graphics(int max_scale);
};

#endif  // INIT_H
