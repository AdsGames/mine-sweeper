#include "button.h"

#include <loadpng.h>

#include "globals.h"

Button::Button() :
  Button(0, 0) {}

Button::Button(int x, int y) {
  this -> x = x;
  this -> y = y;

  height = 10;
  width = 10;

  images[0] = nullptr;
  images[1] = nullptr;
}

Button::~Button() {
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);
}

void Button::setImages(std::string image1, std::string image2) {
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);

  images[0] = load_png(image1.c_str(), NULL);
  images[1] = load_png(image2.c_str(), NULL);

  // Get size from images
  if(images[0] != NULL){
    height = images[0] -> h;
    width = images[0] -> w;
  }
}

bool Button::hovering(){
  if(mouse_x / scale > x &&
     mouse_x / scale < x + width &&
     mouse_y / scale > y &&
     mouse_y / scale < y + height)
    return true;
  return false;
}

void Button::draw(BITMAP* buff){
  // Check hover state
  if(hovering()) {
    if(images[1])
      draw_sprite(buff, images[1], x, y);
    else
      rectfill(buff, x, y, x + width, y + height, 0xFF0000);
  }
  else {
    if(images[0])
      draw_sprite(buff, images[0], x, y);
    else
      rectfill(buff, x, y, x + width, y + height, 0x000000);
  }
}
