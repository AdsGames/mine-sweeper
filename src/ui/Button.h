#ifndef BUTTON_H
#define BUTTON_H

#include <asw/asw.h>
#include <functional>

class Button : public asw::game::Sprite {
 public:
  void update(float deltaTime) override;

  void setImages(const std::string& image1, const std::string& image2);

  void setOnClick(const std::function<void(void)>& func);

 private:
  std::function<void(void)> onClick{nullptr};

  asw::Texture image{nullptr};
  asw::Texture imageHover{nullptr};
};

#endif
