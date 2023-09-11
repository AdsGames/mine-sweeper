#include "Cell.h"

#include <asw/asw.h>
#include <string>

#include "globals.h"
#include "utility/tools.h"

// Shared images
std::array<asw::Texture, 12> Cell::images = {nullptr};

Cell::Cell() : Cell(0, 0, 0, 0) {}

// Create
Cell::Cell(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
  // Load images
  if (!images.at(0).get()) {
    std::string directory = "assets/images/blocks_small/";

    if (game_difficulty == 0)
      directory = "assets/images/blocks/";

    for (int i = 0; i < 12; i++) {
      images.at(i) =
          asw::assets::loadTexture(directory + std::to_string(i) + ".png");
    }
  }
}

// Returns type of block
int Cell::getType() const {
  return type;
}

// Is it flagged?
bool Cell::isFlagged() const {
  return flagged;
}

// Set the type
void Cell::setType(int type) {
  this->type = type;
}

// Get revealed state
bool Cell::isRevealed() const {
  return revealed;
}

// Set revealed
void Cell::reveal() {
  revealed = true;
  flagged = false;
}

// Set whether flagged or not
int Cell::toggleFlag() {
  flagged = !flagged;
  return flagged;
}

// Point over
bool Cell::collisionAt(int x, int y) const {
  return (x >= this->x && x < this->x + width && y >= this->y &&
          y < this->y + height);
}

// Draw
void Cell::draw() const {
  if (flagged) {
    asw::draw::stretchSprite(images.at(10), x, y, width, height);
  } else if (!revealed) {
    asw::draw::stretchSprite(images.at(11), x, y, width, height);
  } else {
    asw::draw::stretchSprite(images.at(type), x, y, width, height);
  }
}
