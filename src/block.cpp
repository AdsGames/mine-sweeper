#include "block.h"

#include <loadpng.h>
#include <string>

#include "globals.h"
#include "tools.h"

// Shared images
BITMAP* Block::images[NUM_IMAGES] = { nullptr };
int Block::block_count = 0;

Block::Block() :
  Block(0, 0, 0, 0) {

}

// Create
Block::Block(int x, int y, int width, int height) {
  // Position
  this -> x = x;
  this -> y = y;

  // Size
  this -> width = width;
  this -> height = height;

  // Other flags
  type = 0;
  revealed = false;
  flagged = false;

  // Load images
  if (block_count == 0) {
    std::string directory = "images/blocks/";
    if (game_difficulty == 16)
      directory = "images/blocks_small/";

    for (int i = 0; i < NUM_IMAGES; i++) {
      images[i] = load_png((directory + convertIntToString(i) + ".png").c_str(), nullptr);
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
      destroy_bitmap(images[i]);
}

// X / Y
int Block::GetX() {
  return x;
}

int Block::GetY() {
  return y;
}

// Width / height
int Block::GetHeight() {
  return height;
}

int Block::GetWidth() {
  return width;
}

// Returns type of block
int Block::GetType() {
  return type;
}

// Is it flagged?
bool Block::IsFlagged() {
  return flagged;
}

// Set the type
void Block::SetType(int type) {
  this -> type = type;
}

// Get revealed state
bool Block::IsRevealed() {
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
bool Block::MouseOver() {
  return collision((float)mouse_x / scale, (float)mouse_x / scale, x, x + width,
                   (float)mouse_y / scale, (float)mouse_y / scale, y, y + height);
}

// Draw
void Block::draw(BITMAP* buff) {
  if (flagged && images[10])
    stretch_sprite(buff, images[10], x, y, width, height);
  else if (!revealed && images[11])
    stretch_sprite(buff, images[11], x, y, width, height);
  else if (images[type])
    stretch_sprite(buff, images[type], x, y, width, height);
}
