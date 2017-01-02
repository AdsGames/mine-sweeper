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
#include "globals.h"
#include "tools.h"
#include "mouseListener.h"

class menu : public state{
  public:
    // Construct/deconstruct
    menu();
    ~menu();

    // Override parent
    void update();
    void draw();

  protected:

  private:
    // Images
    BITMAP* main_menu;
    BITMAP* buffer;

    // Buttons
    Button start_easy;
    Button start_medium;
    Button start_hard;
    Button quit;
};

#endif // MENU_H
