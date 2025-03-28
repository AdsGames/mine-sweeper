#include "./Cell.h"

#include <asw/asw.h>
#include <string>

#include "../globals.h"

// Shared images
std::array<asw::Texture, 12> Cell::images = {nullptr};

// Create
Cell::Cell(const asw::Quad<float>& transform) {
  this->transform = transform;

  // Load images
  if (images.at(0).get() == nullptr) {
    std::string directory = "assets/images/blocks_small/";

    if (game_difficulty == 0) {
      directory = "assets/images/blocks/";
    }

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
  if (revealed || flagged) {
    return;
  }

  revealed = true;
}

// Set whether flagged or not
void Cell::toggleFlag() {
  if (revealed) {
    return;
  }

  flagged = !flagged;
}

void Cell::update(float deltaTime) {
  asw::game::Sprite::update(deltaTime);

  if (revealed) {
    setTexture(images.at(type), false);
  } else if (flagged) {
    setTexture(images.at(10), false);
  } else {
    setTexture(images.at(11), false);
  }
}
