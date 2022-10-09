/*
 * Menu state
 * Allan Legemaate
 * 31/12/2016
 * Menu stuff here!
 */
#ifndef MENU_H
#define MENU_H

#include "State.h"
#include "ui/Button.h"

class Menu : public State {
 public:
  using State::State;

  // Override parent
  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{};

 private:
  // Images
  asw::Texture title;
  asw::Texture main_menu;

  // Buttons
  Button start_easy;
  Button start_medium;
  Button start_hard;
  Button quit;
};

#endif  // MENU_H
