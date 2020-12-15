/*
 * Minefield
 * Allan Legemaate
 * 15/06/2019
 * Provides an interface to interact with cells
 */

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <allegro.h>
#include "Cell.h"

class Minefield {
 public:
  // Construct/destruct
  Minefield();
  Minefield(int width, int height, int num_mines);
  virtual ~Minefield();

  // Get board state
  int getNumMines() const;
  int getNumUnknown() const;
  int getNumFlagged() const;

  // Reveal map
  void revealMap();

  // Reveal at
  int reveal(int x, int y);

  // Flag or unflag tile
  void toggleFlag(int x, int y);

  // Draw map
  void draw(BITMAP* buffer);

 private:
  // Reveal relative
  int revealRelative(int x, int y);

  // Get cell at screen position
  Cell* getCellAt(int x, int y, int* pos_x = nullptr, int* pos_y = nullptr);

  // Generate map
  void generateMap(int x, int y);

  // Cells on screen
  Cell cells[16][16];

  // Variables
  int width, height;

  // Counters
  int num_mines;
  int num_unknown;
  int num_flagged;

  // Don't allow mine on first click
  bool first_reveal;
};

#endif  // MINEFIELD_H
