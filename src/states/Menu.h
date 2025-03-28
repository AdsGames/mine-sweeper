/*
 * Menu state
 * Allan Legemaate
 * 31/12/2016
 * Menu stuff here!
 */
#pragma once

#include <asw/asw.h>

#include "../ui/Button.h"
#include "./State.h"

class Menu : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override;
  void cleanup() override {};
};
