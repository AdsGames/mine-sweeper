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
  // Construct/deconstruct
  Menu();
  virtual ~Menu();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

 private:
  // Disallow copy
  Menu(const Menu&);
  Menu& operator=(const Menu&);

  // Images
  BITMAP* buffer;
  BITMAP* title;
  BITMAP* main_menu;

  // Buttons
  Button start_easy;
  Button start_medium;
  Button start_hard;
  Button quit;
};

#endif  // MENU_H
