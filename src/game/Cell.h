/*
 * Cell
 * Allan Legemaate
 * 15/06/2019
 * An individual cell contained in minefield
 */

#ifndef CELL_H
#define CELL_H

#include <asw/asw.h>
#include <array>

class Cell : public asw::game::Sprite {
 public:
  // Construct and deconstruct
  Cell() = default;

  Cell(const asw::Quad<float>& transform);

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
  void toggleFlag();

  // Draw image to screen
  void update(float deltaTime) override;

 private:
  // Type of cell
  int type{0};

  // Other flags
  bool revealed{false};
  bool flagged{false};

  // Images
  static std::array<asw::Texture, 12> images;
};

#endif
