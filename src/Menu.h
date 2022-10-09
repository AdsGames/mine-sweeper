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
  explicit Menu(StateEngine& engine) : State(engine) {}

  // Override parent
  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override;

 private:
  // Images
  aar::Texture* title;
  aar::Texture* main_menu;

  // Buttons
  Button start_easy;
  Button start_medium;
  Button start_hard;
  Button quit;
};

#endif  // MENU_H
