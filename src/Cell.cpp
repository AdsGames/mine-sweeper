#include "Cell.h"

#include <string>

#include "globals.h"
#include "utility/MouseListener.h"
#include "utility/tools.h"

// Shared images
BITMAP* Cell::images[12] = {nullptr};
int Cell::block_count = 0;

Cell::Cell() : Cell(0, 0, 0, 0) {}

// Create
Cell::Cell(int x, int y, int width, int height)
    : x(x),
      y(y),
      width(width),
      height(height),
      type(0),
      revealed(false),
      flagged(false) {
  // Load images
  if (block_count == 0) {
    std::string directory = "images/blocks_small/";

    if (game_difficulty == 0)
      directory = "images/blocks/";

    for (int i = 0; i < 12; i++) {
      images[i] = load_png_ex(directory + std::to_string(i) + ".png");
    }
  }

  // Inc block count
  block_count++;
}

// Destroy!
Cell::~Cell() {
  block_count--;

  if (block_count <= 0)
    for (int i = 0; i < 12; i++)
      destroy_bitmap(images[i]);
}

// Returns type of block
int Cell::GetType() const {
  return type;
}

// Is it flagged?
bool Cell::IsFlagged() const {
  return flagged;
}

// Set the type
void Cell::SetType(int type) {
  this->type = type;
}

// Get revealed state
bool Cell::IsRevealed() const {
  return revealed;
}

// Set revealed
void Cell::Reveal() {
  revealed = true;
  flagged = false;
}

// Set whether flagged or not
int Cell::ToggleFlag() {
  flagged = !flagged;
  return flagged;
}

// Point over
bool Cell::CollisionAt(int x, int y) const {
  return (x >= this->x && x < this->x + width && y >= this->y &&
          y < this->y + height);
}

// Draw
void Cell::Draw(BITMAP* buffer) {
  if (flagged && images[10])
    stretch_sprite(buffer, images[10], x, y, width, height);
  else if (!revealed && images[11])
    stretch_sprite(buffer, images[11], x, y, width, height);
  else if (images[type])
    stretch_sprite(buffer, images[type], x, y, width, height);
}
