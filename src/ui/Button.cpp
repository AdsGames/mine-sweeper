#include "Button.h"

#include <asw/util/MouseListener.h>

#include "../utility/tools.h"

Button::Button() : Button(0, 0) {}

Button::Button(int x, int y) : x(x), y(y) {}

void Button::SetOnClick(std::function<void(void)> func) {
  OnClick = func;
}

// Load images from file
void Button::SetImages(const std::string& image1, const std::string& image2) {
  images[0] = asw::load::texture(image1);
  images[1] = asw::load::texture(image2);

  // Size
  auto size = asw::util::getTextureSize(images[0]);
  height = size.y;
  width = size.x;
}

bool Button::Hover() const {
  return (signed)MouseListener::x > x && (signed)MouseListener::x < x + width &&
         (signed)MouseListener::y > y && (signed)MouseListener::y < y + height;
}

void Button::Update() {
  if (Hover() && MouseListener::mouse_pressed & 1 && OnClick != nullptr) {
    OnClick();
  }
}

void Button::Draw() {
  const auto imageIndex = static_cast<int>(Hover());

  if (images[imageIndex]) {
    asw::draw::sprite(images[imageIndex], x, y);
  } else {
    asw::draw::primRectFill(x, y, x + width, y + height,
                            asw::util::makeColor(153, 153, 153));
  }
}
