#include "tools.h"

#include <sstream>

//Collision
bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2){
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1){
    return true;
  }
  return false;
}

//Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}

//Convert int to string
std::string convertIntToString(int number){
  std::stringstream ss;
  ss << number;
  return ss.str();
}

// Fade in
void highcolor_fade_in(BITMAP* bmp_orig, int speed){
  BITMAP *bmp_buff = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP *str_orig = create_bitmap(SCREEN_W, SCREEN_H);
  stretch_sprite(str_orig, bmp_orig, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0)
    speed = 16;

  for (int a = 0; a < 256; a += speed) {
    clear(bmp_buff);
    set_trans_blender(0, 0, 0, a);
    draw_trans_sprite(bmp_buff, str_orig, 0, 0);
    vsync();
    stretch_sprite(screen, bmp_buff, 0, 0, SCREEN_W, SCREEN_H);
  }
  stretch_sprite(screen, str_orig, 0, 0, SCREEN_W, SCREEN_H);
  destroy_bitmap(str_orig);
  destroy_bitmap(bmp_buff);
}

// Fade out
void highcolor_fade_out(int speed) {
  BITMAP *bmp_buff = create_bitmap(SCREEN_W,SCREEN_H);
  BITMAP *bmp_orig = create_bitmap(SCREEN_W, SCREEN_H);
  blit(screen, bmp_orig, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0)
    speed = 16;

  for (int a = 255 - speed; a > 0; a -= speed) {
    clear(bmp_buff);
    set_trans_blender(0, 0, 0, a);
    draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
    vsync();
    stretch_sprite(screen, bmp_buff, 0, 0,  SCREEN_W, SCREEN_H);
  }
  rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, makecol(0,0,0));
  destroy_bitmap(bmp_orig);
  destroy_bitmap(bmp_buff);
}

/*
 *  ERROR REPORTING
 */
void abort_on_error(const char *message){
	 if(screen != NULL) {
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message, allegro_error);
	 exit(-1);
}
