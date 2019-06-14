#include "block.h"

#include <string>

#include "globals.h"
#include "tools.h"
#include "mouseListener.h"

// Shared images
BITMAP *Block::images[NUM_IMAGES] = { nullptr };
int Block::block_count = 0;

Block::Block() :
  Block (0, 0, 0, 0) {

}

// Create
Block::Block (int x, int y, int width, int height)
  : x(x),
    y(y),
    width(width),
    height(height),
    type(0),
    revealed(false),
    flagged(false) {

  // Load images
  if (block_count == 0) {
    std::string directory = "images/blocks/";

    if (game_difficulty == 16)
      directory = "images/blocks_small/";

    for (int i = 0; i < NUM_IMAGES; i++) {
      images[i] = load_png_ex (directory + std::to_string(i) + ".png");
    }
  }

  // Inc block count
  block_count ++;
}

// Destroy!
Block::~Block() {
  block_count --;

  if (block_count <= 0)
    for (int i = 0; i < NUM_IMAGES; i++)
      destroy_bitmap (images[i]);
}

// Returns type of block
int Block::GetType()  const {
  return type;
}

// Is it flagged?
bool Block::IsFlagged()  const {
  return flagged;
}

// Set the type
void Block::SetType (int type) {
  this -> type = type;
}

// Get revealed state
bool Block::IsRevealed()  const {
  return revealed;
}

// Set revealed
void Block::Reveal() {
  revealed = true;
  flagged = false;
}

// Set whether flagged or not
void Block::Flag() {
  flagged = true;
}

void Block::Unflag() {
  flagged = false;
}

// Mouse over
bool Block::MouseOver() const {
  return collision (mouseListener::x, mouseListener::x, x, x + width,
                    mouseListener::y, mouseListener::y, y, y + height);
}

// Draw
void Block::draw (BITMAP *buff) {
  if (flagged && images[10])
    stretch_sprite (buff, images[10], x, y, width, height);
  else if (!revealed && images[11])
    stretch_sprite (buff, images[11], x, y, width, height);
  else if (images[type])
    stretch_sprite (buff, images[type], x, y, width, height);
}
