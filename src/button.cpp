#include "button.h"

#include <loadpng.h>

#include "globals.h"

Button::Button() {
  height = 0;
  width = 0;

  images[0] = NULL;
  images[1] = NULL;
}

Button::~Button() {
  // Destroy bitmaps
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);
}

void Button::set_images(std::string image1, std::string image2){
  images[0] = load_png(image1.c_str(), NULL);
  images[1] = load_png(image2.c_str(), NULL);

  // Get size from images
  if(images[0] != NULL){
    height = images[0] -> h;
    width = images[0] -> w;
  }
}

bool Button::get_hover(){
  if(mouse_x / scale > x &&
     mouse_x / scale < x + width &&
     mouse_y / scale > y &&
     mouse_y / scale < y + height)
    return true;
  return false;
}

void Button::set_position(int x, int y) {
  this -> x = x;
  this -> y = y;
}

int Button::get_x() {
  return x;
}

int Button::get_y(){
  return y;
}

void Button::draw(BITMAP* buff){
  // Check hover state
  if(get_hover()) {
    if(images[1] != NULL)
      draw_sprite(buff, images[1], x, y);
    else
      rectfill(buff, x, y, x + 10, y + 10, 0xFF0000);
  }
  else {
    if(images[0] != NULL)
      draw_sprite(buff, images[0], x, y);
    else
      rectfill(buff, x, y, x + 10, y + 10, 0xFF0000);
  }
}
