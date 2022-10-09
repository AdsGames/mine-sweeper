#include "Minefield.h"

#include "globals.h"
#include "utility/tools.h"

Minefield::Minefield() : Minefield(1, 1, 0) {}

Minefield::Minefield(int width, int height, int num_mines)
    : width(width),
      height(height),
      num_mines(num_mines),
      num_unknown(width * height - num_mines),
      num_flagged(0),
      first_reveal(false) {
  // Check parameters
  if (width < 1)
    width = 1;

  if (height < 1)
    height = 1;

  // Init blocks
  auto screenSize = asw::display::getLogicalSize();
  int cell_size = screenSize.x / width;
  int offset = (screenSize.x % cell_size) / 2;

  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      cells[i][t] = Cell(i * cell_size + offset, t * cell_size + offset,
                         cell_size, cell_size);
    }
  }
}

Minefield::~Minefield() {}

// Get board state
int Minefield::getNumMines() const {
  return num_mines;
}

int Minefield::getNumUnknown() const {
  return num_unknown;
}

int Minefield::getNumFlagged() const {
  return num_flagged;
}

// Generate minefield
void Minefield::generateMap(int x, int y) {
  // Plant mines
  int num_placed = 0;

  while (num_placed < num_mines) {
    int random_x = random(0, width - 1);
    int random_y = random(0, height - 1);

    if (cells[random_x][random_y].getType() != 9 && random_x != x &&
        random_y != y) {
      cells[random_x][random_y].setType(9);
      num_placed++;
    }
  }

  // Number based on surrounding mines
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      if (cells[i][t].getType() != 9) {
        int type = 0;

        // Surrounding 8 cells
        for (int j = i - 1; j <= i + 1; j++) {
          for (int k = t - 1; k <= t + 1; k++) {
            if (j >= 0 && j < width && k >= 0 && k < height) {
              type += cells[j][k].getType() == 9;
            }
          }
        }

        cells[i][t].setType(type);
      }
    }
  }
}

// Reveal some blocks recursively
int Minefield::reveal(int x, int y) {
  // Find cell position
  int cell_x, cell_y;

  if (!getCellAt(x, y, &cell_x, &cell_y))
    return -1;

  // Generate map on first click
  if (!first_reveal) {
    generateMap(cell_x, cell_y);
    first_reveal = true;
  }

  return revealRelative(cell_x, cell_y);
}

// Reveal relative
int Minefield::revealRelative(int x, int y) {
  if (x < 0 || y < 0 || x >= width || y >= height)
    return -1;

  Cell* temp = &cells[x][y];

  if (!temp || temp->isRevealed() || temp->isFlagged())
    return -1;

  temp->reveal();
  num_unknown--;

  if (temp->getType() == 0) {
    for (int j = x - 1; j <= x + 1; j++) {
      for (int k = y - 1; k <= y + 1; k++) {
        if (!(j == x && k == y) && cells[j][k].getType() != 9) {
          revealRelative(j, k);
        }
      }
    }
  }

  return temp->getType();
}

void Minefield::revealMap() {
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      cells[i][t].reveal();
    }
  }
}

void Minefield::toggleFlag(int x, int y) {
  Cell* temp = getCellAt(x, y);

  if (!temp || temp->isRevealed())
    return;

  num_flagged += (temp->toggleFlag() * 2) - 1;
}

// Get cell at screen position
Cell* Minefield::getCellAt(int x, int y, int* pos_x, int* pos_y) {
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      if (cells[i][t].collisionAt(x, y)) {
        if (pos_x) {
          *pos_x = i;
        }

        if (pos_y) {
          *pos_y = t;
        }

        return &cells[i][t];
      }
    }
  }

  return nullptr;
}

// Draw map
void Minefield::draw() {
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      cells[i][t].draw();
    }
  }
}
