#include "Cell.h"

#include <asw/asw.h>
#include <asw/util/MouseListener.h>
#include <string>

#include "globals.h"
#include "utility/tools.h"

// Shared images
asw::Texture Cell::images[12] = {nullptr};

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
  if (!images[0].get()) {
    std::string directory = "assets/images/blocks_small/";

    if (game_difficulty == 0)
      directory = "assets/images/blocks/";

    for (int i = 0; i < 12; i++) {
      images[i] = asw::load::texture(directory + std::to_string(i) + ".png");
    }
  }
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
void Cell::Draw() {
  if (flagged) {
    asw::draw::stretchSprite(images[10], x, y, width, height);
  } else if (!revealed) {
    asw::draw::stretchSprite(images[11], x, y, width, height);
  } else {
    asw::draw::stretchSprite(images[type], x, y, width, height);
  }
}
