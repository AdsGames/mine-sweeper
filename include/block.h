#ifndef BLOCK_H
#define BLOCK_H

#include <allegro.h>
#include <string>
#include <time.h>

#include <sstream>

#include "tools.h"

// Block class!
class Block{
  public:
    // Construct and deconstruct
    Block();
    ~Block();

    // Set images for block
    void SetImages(std::string new_image);

    // X / Y
    int GetX() { return x; }
    int GetY() { return y; }

    // Width / height
    int GetHeight() { return height; }
    int GetWidth() { return width; }

    // Returns type of block
    int GetType() { return type; }

    // Mouse selected or not
    bool GetSelected() { return selected; }

    // Is it flagged?
    bool GetFlagged() { return flagged; }

    // Set the type
    void SetType(int type) { this -> type = type; }

    // Set whether already selected
    void SetSelected(bool selected) { this -> selected = selected; }

    // Set whether flagged or not
    void SetFlagged(bool flagged) { this -> flagged = flagged; }

    // Set Position
    void SetX(int x) { this -> x = x; }
    void SetY(int y) { this -> y = y; }

    // Set Size
    void SetWidth(float width) { this -> width = width; }
    void SetHeight(float height) { this -> height = height; }

    // Change type
    void Change();

    // Draw image to screen
    void draw(BITMAP* tempBitmap);
  private:
    // Position
    int x;
    int y;

    // Size
    float width;
    float height;

    // Other flags
    int type;
    bool selected;
    bool flagged;

    // Images
    BITMAP *image;
    BITMAP *flag;
};

#endif
