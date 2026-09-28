/*
 * Menu state
 * Allan Legemaate
 * 31/12/2016
 * Menu stuff here!
 */
#pragma once

#include <asw/asw.h>
#include <memory>

#include "./State.h"

class Menu : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  // Override parent
  void init() override;
  void update(float dt) override;
  void draw() override;

 private:
  std::unique_ptr<asw::ui::Root> ui;
};
