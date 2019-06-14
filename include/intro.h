/*
 * Intro State
 * Allan Legemaate
 * 31/12/2016
 * Just some splashes
 */
#ifndef INTRO_H
#define INTRO_H

#include "state.h"

class intro : public state {
  public:
    // Construct/deconstruct
    intro();
    virtual ~intro();

    // Override parent
    virtual void update() override {};
    virtual void draw() override;

  private:
    BITMAP *img_intro;
    BITMAP *img_title;
};

#endif // INTRO_H
