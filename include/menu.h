/*
 * Menu state
 * Allan Legemaate
 * 31/12/2016
 * Menu stuff here!
 */
#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "button.h"

class menu : public state{
  public:
    // Construct/deconstruct
    menu();
    ~menu();

    // Override parent
    void update();
    void draw();

  private:
    // Images
    BITMAP* title;
    BITMAP* main_menu;
    BITMAP* buffer;

    // Buttons
    Button start_easy;
    Button start_medium;
    Button start_hard;
    Button quit;
};

#endif // MENU_H
