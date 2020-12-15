#include "Button.h"

#include "../utility/MouseListener.h"
#include "../utility/tools.h"

Button::Button() : Button(0, 0) {}

Button::Button(int x, int y)
    : OnClick(nullptr), x(x), y(y), width(10), height(10) {
  images[0] = nullptr;
  images[1] = nullptr;
}

Button::Button(const Button& b)
    : OnClick(b.OnClick), x(b.x), y(b.y), width(b.width), height(b.height) {
  if (b.images[0]) {
    images[0] = create_bitmap(b.images[0]->w, b.images[0]->h);
    draw_sprite(images[0], b.images[0], 0, 0);
  }

  if (b.images[1]) {
    images[1] = create_bitmap(b.images[1]->w, b.images[1]->h);
    draw_sprite(images[1], b.images[1], 0, 0);
  }
}

Button& Button::operator=(const Button& b) {
  if (this == &b)
    return *this;

  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);

  x = b.x;
  y = b.y;
  OnClick = b.OnClick;
  width = b.width;
  height = b.height;

  if (b.images[0]) {
    images[0] = create_bitmap(b.images[0]->w, b.images[0]->h);
    draw_sprite(images[0], b.images[0], 0, 0);
  }

  if (b.images[1]) {
    images[1] = create_bitmap(b.images[1]->w, b.images[1]->h);
    draw_sprite(images[1], b.images[1], 0, 0);
  }

  return *this;
}

Button::~Button() {
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);
}

void Button::SetOnClick(std::function<void(void)> func) {
  OnClick = func;
}

// Load images from file
void Button::SetImages(const char* image1, const char* image2) {
  images[0] = load_png_ex(image1);
  images[1] = load_png_ex(image2);

  // Size
  height = images[0]->h;
  width = images[0]->w;
}

bool Button::Hover() const {
  return (signed)MouseListener::x > x && (signed)MouseListener::x < x + width &&
         (signed)MouseListener::y > y && (signed)MouseListener::y < y + height;
}

void Button::Update() {
  if (Hover() && MouseListener::mouse_pressed & 1 && OnClick != nullptr)
    OnClick();
}

void Button::Draw(BITMAP* buffer) {
  if (images[Hover()]) {
    draw_sprite(buffer, images[Hover()], x, y);
  } else {
    rectfill(buffer, x, y, x + width, y + height, 0x999999);
  }
}
