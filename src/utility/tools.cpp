#include "utility/tools.h"

#include <sstream>
#include <random>
#include <loadpng.h>

// Random device
std::mt19937 rng (time (nullptr));

//Random number generator. Use int random(lowest,highest);
int random (int low, int high) {
  std::uniform_int_distribution<int> dist (low, high); // distribution in range [1, 6]
  return dist (rng);
}

// Fade in
void highcolor_fade_in (BITMAP *bmp_orig, int speed) {
  BITMAP *bmp_buff = create_bitmap (SCREEN_W, SCREEN_H);
  BITMAP *str_orig = create_bitmap (SCREEN_W, SCREEN_H);
  stretch_sprite (str_orig, bmp_orig, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0)
    speed = 16;

  for (int a = 0; a < 256; a += speed) {
    clear (bmp_buff);
    set_trans_blender (0, 0, 0, a);
    draw_trans_sprite (bmp_buff, str_orig, 0, 0);
    vsync();
    stretch_sprite (screen, bmp_buff, 0, 0, SCREEN_W, SCREEN_H);
  }

  stretch_sprite (screen, str_orig, 0, 0, SCREEN_W, SCREEN_H);
  destroy_bitmap (str_orig);
  destroy_bitmap (bmp_buff);
}

// Fade out
void highcolor_fade_out (int speed) {
  BITMAP *bmp_buff = create_bitmap (SCREEN_W, SCREEN_H);
  BITMAP *bmp_orig = create_bitmap (SCREEN_W, SCREEN_H);
  blit (screen, bmp_orig, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0)
    speed = 16;

  for (int a = 255 - speed; a > 0; a -= speed) {
    clear (bmp_buff);
    set_trans_blender (0, 0, 0, a);
    draw_trans_sprite (bmp_buff, bmp_orig, 0, 0);
    vsync();
    stretch_sprite (screen, bmp_buff, 0, 0,  SCREEN_W, SCREEN_H);
  }

  rectfill (screen, 0, 0, SCREEN_W, SCREEN_H, makecol (0, 0, 0));
  destroy_bitmap (bmp_orig);
  destroy_bitmap (bmp_buff);
}

// Error reporting
void abort_on_error (std::string message) {
  if (screen != NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
  }

  allegro_message ("%s.\n %s\n", message.c_str(), allegro_error);
  exit (-1);
}

// Load image
BITMAP *load_png_ex (std::string path) {
  BITMAP *temp = nullptr;

  if (! (temp = load_png (path.c_str(), nullptr)))
    abort_on_error ("Cannot find image (" + path + ") \n Please check your files and try again");

  return temp;
}

// Load sample
SAMPLE *load_sample_ex (std::string path) {
  SAMPLE *temp = nullptr;

  if (! (temp = load_sample (path.c_str())))
    abort_on_error ("Cannot find image (" + path + ") \n Please check your files and try again");

  return temp;
}
