/*
 * Minefield
 * Allan Legemaate
 * 15/06/2019
 * Provides an interface to interact with cells
 */

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <asw/asw.h>
#include <vector>

#include "./Cell.h"

class Minefield {
 public:
  // Construct/destruct
  Minefield();
  Minefield(int width, int height, int num_mines);

  // Get board state
  int getNumMines() const;
  int getNumUnknown() const;
  int getNumFlagged() const;

  // Reveal map
  void revealMap();

  // Reveal at
  int reveal(float x, float y);

  // Flag or unflag tile
  void toggleFlag(float x, float y);

  // Draw map
  void draw();

  // Update map
  void update(float deltaTime);

 private:
  // Get cell at screen position
  Cell* getCellAt(float x, float y, int* pos_x = nullptr, int* pos_y = nullptr);

  // Reveal relative
  void revealArea(int x, int y);

  // Generate map
  void generateMap(int x, int y);

  // Cells on screen
  std::vector<std::vector<Cell>> cells;

  // Variables
  int width;
  int height;

  // Counters
  int num_mines;
  int num_unknown;
  int num_flagged;

  // Don't allow mine on first click
  bool first_reveal;
};

#endif  // MINEFIELD_H
