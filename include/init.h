/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include "state.h"

#define BUFFER_WIDTH 128
#define BUFFER_HEIGHT 128
#define DEFAULT_SCALE 4

class init : public state {
  public:
    // Construct/deconstruct
    init();
    ~init() {};

    // Defaults graphics mode
    int set_graphics (int max_scale);

    // Override parent
    void update();
    void draw() {};
};

#endif // INIT_H
