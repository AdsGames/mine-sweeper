/*
 * Menu state
 * Allan Legemaate
 * 31/12/2016
 * Menu stuff here!
 */
#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "ui/Button.h"

class menu : public state {
  public:
    // Construct/deconstruct
    menu();
    virtual ~menu();

    // Override parent
    virtual void update() override;
    virtual void draw() override;

  private:
    // Images
    BITMAP *title;
    BITMAP *main_menu;
    BITMAP *buffer;

    // Buttons
    Button start_easy;
    Button start_medium;
    Button start_hard;
    Button quit;
};

#endif // MENU_H
