/*
 * Cell
 * Allan Legemaate
 * 15/06/2019
 * An individual cell contained in minefield
 */

#ifndef CELL_H
#define CELL_H

#include <asw/asw.h>

class Cell {
 public:
  // Construct and deconstruct
  Cell();
  Cell(int x, int y, int width, int height);

  // Returns type of block
  int getType() const;

  // Mouse selected or not
  bool isRevealed() const;

  // Is it flagged?
  bool isFlagged() const;

  // Set the type
  void setType(int type);

  // Set whether already selected
  void reveal();

  // Set whether flagged or not
  int toggleFlag();

  // Point over
  bool collisionAt(int x, int y) const;

  // Draw image to screen
  void draw() const;

 private:
  // Position
  int x;
  int y;

  // Size
  int width;
  int height;

  // Type of cell
  int type{0};

  // Other flags
  bool revealed{false};
  bool flagged{false};

  // Images
  static asw::Texture images[12];
};

#endif
