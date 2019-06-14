/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include "State.h"

#define BUFFER_WIDTH 128
#define BUFFER_HEIGHT 128
#define DEFAULT_SCALE 4

class init : public state {
  public:
    // Construct/deconstruct
    init();
    virtual ~init() {};

    // Override parent
    virtual void update() override;
    virtual void draw() override {};

    // Defaults graphics mode
    static int set_graphics (int max_scale);
};

#endif // INIT_H
