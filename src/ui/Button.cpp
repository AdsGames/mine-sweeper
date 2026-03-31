#include "Button.h"

#include <asw/asw.h>

void Button::setOnClick(const std::function<void(void)>& func) {
  onClick = func;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  image = asw::assets::load_texture(image1);
  imageHover = asw::assets::load_texture(image2);
  transform.size = asw::util::get_texture_size(image);
}

void Button::update(float _dt) {
  const auto mouse = asw::input::get_mouse();
  const auto hovering =
      transform.contains({mouse.position.x, mouse.position.y});

  if (hovering &&
      asw::input::get_mouse_button_down(asw::input::MouseButton::Left) &&
      onClick != nullptr) {
    onClick();
  }

  if (hovering) {
    set_texture(imageHover);
  } else {
    set_texture(image);
  }
}
