/*
 * Cell
 * Allan Legemaate
 * 15/06/2019
 * An individual cell contained in minefield
 */

#ifndef CELL_H
#define CELL_H

#include "./lib/aar/aar.h"

class Cell {
 public:
  // Construct and deconstruct
  Cell();
  Cell(int x, int y, int width, int height);
  ~Cell();

  // Returns type of block
  int GetType() const;

  // Mouse selected or not
  bool IsRevealed() const;

  // Is it flagged?
  bool IsFlagged() const;

  // Set the type
  void SetType(int type);

  // Set whether already selected
  void Reveal();

  // Set whether flagged or not
  int ToggleFlag();

  // Point over
  bool CollisionAt(int x, int y) const;

  // Draw image to screen
  void Draw();

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
  static aar::Texture* images[12];
  static int block_count;
};

#endif
