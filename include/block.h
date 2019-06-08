#ifndef BLOCK_H
#define BLOCK_H

#include <allegro.h>

#define NUM_IMAGES 12

// Block class!
class Block {
  public:
    // Construct and deconstruct
    Block();
    Block (int x, int y, int width, int height);
    ~Block();

    // X / Y
    int GetX();
    int GetY();

    // Width / height
    int GetHeight();
    int GetWidth();

    // Returns type of block
    int GetType();

    // Mouse selected or not
    bool IsRevealed();

    // Is it flagged?
    bool IsFlagged();

    // Set the type
    void SetType (int type);

    // Set whether already selected
    void Reveal();

    // Set whether flagged or not
    void Flag();
    void Unflag();

    // Mouse over
    bool MouseOver();

    // Draw image to screen
    void draw (BITMAP *buff);

  private:
    // Position
    int x;
    int y;

    // Size
    int width;
    int height;

    // Other flags
    int type;
    bool revealed;
    bool flagged;

    // Images
    static BITMAP *images[NUM_IMAGES];
    static int block_count;
};

#endif
