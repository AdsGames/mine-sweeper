#include "ImageButton.h"

#include <utility>

ImageButton::ImageButton(const std::string& image,
                         const std::string& hover_image,
                         const asw::Vec2<float>& position,
                         std::function<void()> on_click)
    : hover_texture(asw::assets::load_texture(hover_image)) {
  set_texture(asw::assets::load_texture(image), true);
  transform.position = position;
  this->on_click = std::move(on_click);
}

void ImageButton::draw(asw::ui::Context& ctx) {
  // Keyboard and controller focus highlights the same as mouse hover
  const bool highlighted = _hovered || (_focused && ctx.theme.show_focus);

  asw::draw::sprite(highlighted ? hover_texture : texture, transform.position);

  Widget::draw(ctx);
}
