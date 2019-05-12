#include "block.h"

// Create
Block::Block() {
  // Position
  x = y = 0;

  // Size
  width = height = 0;

  // Other flags
  type = 0;
  selected = false;
  flagged = false;

  // Set images to null
  flag = NULL;
  image = NULL;
}

// Destroy!
Block::~Block() {
  destroy_bitmap(flag);
  destroy_bitmap(image);
}

// Load 1 image
void Block::SetImages(std::string new_image) {
  // Load new images
  image = load_png(new_image.c_str(), NULL);

  // Only load flag if not done so already
  if(flag == NULL)
    flag = load_png("images/blocks/flag.png" , NULL);
}

// Load new image
void Block::Change() {
  // Destroy old images
  destroy_bitmap(image);

  // Change image
  SetImages(std::string("images/blocks/" + convertIntToString(type) + ".png"));
}

// Draw
void Block::draw(BITMAP* tempBitmap) {
  if(image != NULL) {
    stretch_sprite(tempBitmap, image, x, y, width, height);
  }
  if(flagged && flag != NULL) {
    stretch_sprite(tempBitmap, flag, x, y, width, height);
  }
}
