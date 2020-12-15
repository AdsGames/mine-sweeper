/*
 * Intro State
 * Allan Legemaate
 * 31/12/2016
 * Just some splashes
 */
#ifndef INTRO_H
#define INTRO_H

#include <allegro.h>
#include "State.h"

class Intro : public State {
 public:
  // Construct/deconstruct
  Intro();
  virtual ~Intro();

  // Override parent
  virtual void update() override{};
  virtual void draw() override;

 private:
  // Disallow copy
  Intro(const Intro&);
  Intro& operator=(const Intro&);

  // Images
  BITMAP* img_intro;
  BITMAP* img_title;
};

#endif  // INTRO_H
