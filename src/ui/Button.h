#ifndef BUTTON_H
#define BUTTON_H

#include <asw/asw.h>
#include <functional>

class Button {
 public:
  Button();
  Button(int x, int y);

  void Update();

  void SetImages(const std::string& image1, const std::string& image2);

  void SetOnClick(std::function<void()> func);

  void Draw();

  bool Hover() const;

 private:
  std::function<void(void)> OnClick{nullptr};

  int x, y;
  int width{10};
  int height{10};

  asw::Texture images[2]{nullptr};
};

#endif
