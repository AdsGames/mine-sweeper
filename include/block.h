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

    // Returns type of block
    int GetType() const;

    // Mouse selected or not
    bool IsRevealed() const;

    // Is it flagged?
    bool IsFlagged() const;

    // Set the type
    void SetType (int type);

    // Set whether already selected
    void Reveal();

    // Set whether flagged or not
    void Flag();
    void Unflag();

    // Mouse over
    bool MouseOver() const;

    // Draw image to screen
    void draw (BITMAP *buff);

  private:
    // Position
    int x, y;

    // Size
    int width, height;

    // Other flags
    int type;
    bool revealed;
    bool flagged;

    // Images
    static BITMAP *images[NUM_IMAGES];
    static int block_count;
};

#endif
