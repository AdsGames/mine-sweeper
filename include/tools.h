#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <allegro.h>

//Collision
extern bool collision (float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2);

//Random number generator
extern int random (int low, int high);

// Fade in and out
extern void highcolor_fade_in (BITMAP *bmp_orig, int speed);
extern void highcolor_fade_out (int speed);

// Error reporting
extern void abort_on_error (std::string message);

// Load image
extern BITMAP *load_png_ex (std::string path);

// Load sample
extern SAMPLE *load_sample_ex (std::string path);

#endif
