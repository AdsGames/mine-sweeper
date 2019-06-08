/*
 * Button Class
 * Allan Legemaate
 * 31/12/2016
 * Redone to be more intuitive
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <allegro.h>
#include <string>

class Button {
  public:
    Button();
    Button (int x, int y);
    ~Button();

    void setImages (std::string image1, std::string image2);

    bool hovering();

    void draw (BITMAP *buff);

  private:
    int height;
    int width;

    int x;
    int y;

    BITMAP *images[2];
};

#endif

