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
    void SetImages( std::string new_image);

    // X / Y
    int GetX(){ return x; }
    int GetY(){ return y; }

    // Width / height
    int GetHeight(){ return height; }
    int GetWidth(){ return width; }

    // Returns type of block
    int GetType(){ return type; }

    // Mouse selected or not
    bool GetSelected(){ return selected; }

    // Is it flagged?
    bool GetFlaged(){ return flaged; }

    // Set the type
    void SetType(int newType){ type = newType; }

    // Set whether already selected
    void SetSelected(bool newSelected){ selected = newSelected; }

    // Set whether flagged or not
    void SetFlaged(bool newFlag){ flaged = newFlag; }

    // Set Position
    void SetX( int newValue){ x = newValue; }
    void SetY( int newValue){ y = newValue; }

    // Set Size
    void SetWidth( float newValue){ width = newValue; }
    void SetHeight( float newValue){ height = newValue; }

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
    bool flaged;

    // Images
    BITMAP *image;
    BITMAP *flag;
};

#endif
