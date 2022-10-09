#include "Button.h"

#include "../utility/MouseListener.h"
#include "../utility/tools.h"

Button::Button() : Button(0, 0) {}

Button::~Button() {
  aar::load::destroyTexture(images[0]);
  aar::load::destroyTexture(images[1]);
}

Button::Button(int x, int y)
    : OnClick(nullptr), x(x), y(y), width(10), height(10) {
  images[0] = nullptr;
  images[1] = nullptr;
}

void Button::SetOnClick(std::function<void(void)> func) {
  OnClick = func;
}

// Load images from file
void Button::SetImages(const char* image1, const char* image2) {
  images[0] = aar::load::bitmap(image1);
  images[1] = aar::load::bitmap(image2);

  // Size
  auto size = aar::util::getTextureSize(images[0]);
  height = size.y;
  width = size.x;
}

bool Button::Hover() const {
  return (signed)MouseListener::x > x && (signed)MouseListener::x < x + width &&
         (signed)MouseListener::y > y && (signed)MouseListener::y < y + height;
}

void Button::Update() {
  if (Hover() && MouseListener::mouse_pressed & 1 && OnClick != nullptr)
    OnClick();
}

void Button::Draw() {
  if (images[Hover()]) {
    aar::draw::sprite(images[Hover()], x, y);
  } else {
    aar::draw::primRectFill(x, y, x + width, y + height,
                            aar::util::makeColor(153, 153, 153));
  }
}
