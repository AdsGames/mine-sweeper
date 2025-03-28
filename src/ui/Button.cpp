#include "Button.h"

#include <asw/asw.h>

void Button::setOnClick(const std::function<void(void)>& func) {
  onClick = func;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  image = asw::assets::loadTexture(image1);
  imageHover = asw::assets::loadTexture(image2);
  transform.size = asw::util::getTextureSize(image);
}

void Button::update(float _deltaTime) {
  const auto hovering =
      transform.contains({asw::input::mouse.x, asw::input::mouse.y});

  if (hovering && asw::input::mouse.pressed[1] && onClick != nullptr) {
    onClick();
  }

  if (hovering) {
    setTexture(imageHover);
  } else {
    setTexture(image);
  }
}
