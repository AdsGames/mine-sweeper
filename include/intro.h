/*
 * Intro State
 * Allan Legemaate
 * 31/12/2016
 * Just some splashes
 */
#ifndef INTRO_H
#define INTRO_H

#include "state.h"
#include "tools.h"

class intro : public state{
  public:
    // Construct/deconstruct
    intro();
    ~intro();

    // Override parent
    void update() {};
    void draw();

  protected:

  private:
    BITMAP* img_intro;
    BITMAP* img_title;
};

#endif // INTRO_H
