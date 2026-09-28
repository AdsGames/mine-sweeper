#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include <asw/asw.h>
#include <functional>
#include <string>

// An asw ui button drawn with an image, and a second image when highlighted
class ImageButton : public asw::ui::Button {
 public:
  ImageButton(const std::string& image,
              const std::string& hover_image,
              const asw::Vec2<float>& position,
              std::function<void()> on_click);

  void draw(asw::ui::Context& ctx) override;

 private:
  asw::Texture hover_texture;
};

#endif
