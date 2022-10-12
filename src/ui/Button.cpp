#include "Button.h"

#include <asw/util/MouseListener.h>

#include "../utility/tools.h"

Button::Button() : Button(0, 0) {}

Button::Button(int x, int y) : x(x), y(y) {}

void Button::setOnClick(std::function<void(void)> func) {
  onClick = func;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  image = asw::load::texture(image1);
  imageHover = asw::load::texture(image2);

  // Size
  auto size = asw::util::getTextureSize(image);
  height = size.y;
  width = size.x;
}

bool Button::isHovering() const {
  return (signed)MouseListener::x > x && (signed)MouseListener::x < x + width &&
         (signed)MouseListener::y > y && (signed)MouseListener::y < y + height;
}

void Button::update() const {
  if (isHovering() && MouseListener::mouse_pressed & 1 && onClick != nullptr) {
    onClick();
  }
}

void Button::draw() const {
  if (isHovering() && imageHover) {
    asw::draw::sprite(imageHover, x, y);
  } else if (!isHovering() && image) {
    asw::draw::sprite(image, x, y);
  } else {
    asw::draw::primRectFill(x, y, x + width, y + height,
                            asw::util::makeColor(153, 153, 153));
  }
}
