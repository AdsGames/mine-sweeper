#ifndef BUTTON_H
#define BUTTON_H

#include <asw/asw.h>
#include <functional>

class Button {
 public:
  Button();
  Button(int x, int y);

  void update() const;

  void setImages(const std::string& image1, const std::string& image2);

  void setOnClick(std::function<void()> func);

  void draw() const;

  bool isHovering() const;

 private:
  std::function<void(void)> onClick{nullptr};

  int x;
  int y;

  int width{10};
  int height{10};

  asw::Texture image{nullptr};
  asw::Texture imageHover{nullptr};
};

#endif
