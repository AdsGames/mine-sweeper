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

class Button{
  public:
    Button();
    ~Button();

    void set_images(std::string image1, std::string image2);

    bool get_hover();

    void draw(BITMAP* buff);

    void set_position(int x, int y);

    void set_type(int type);
    void set_value(int value);

    int get_x();
    int get_y();

  private:
    int height;
    int width;

    int x;
    int y;

    BITMAP *images[2];
};

#endif

