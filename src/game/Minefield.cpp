#include "./Minefield.h"

#include <algorithm>
#include <array>
#include <stack>
#include <utility>

#include "../globals.h"

Minefield::Minefield() : Minefield(1, 1, 0) {}

Minefield::Minefield(int width, int height, int num_mines)
    : width(std::max(width, 1)),
      height(std::max(height, 1)),
      num_mines(std::clamp(num_mines, 0, (this->width * this->height) - 1)),
      num_unknown((this->width * this->height) - this->num_mines),
      num_flagged(0),
      num_revealed(0),
      first_reveal(false) {
  // Init blocks
  auto screenSize = asw::display::get_logical_size();
  const int cell_size = std::min(screenSize.x / this->width,
                                 screenSize.y / this->height);
  const int offset_x = (screenSize.x - (cell_size * this->width)) / 2;
  const int offset_y = (screenSize.y - (cell_size * this->height)) / 2;

  for (int i = 0; i < this->width; i++) {
    cells.emplace_back();

    for (int t = 0; t < this->height; t++) {
      cells.at(i).emplace_back(asw::Quad<float>(i * cell_size + offset_x,
                                                t * cell_size + offset_y,
                                                cell_size, cell_size));
    }
  }
}

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

// All safe cells revealed
bool Minefield::isCleared() const {
  return num_revealed == (width * height) - num_mines;
}

// Generate minefield
void Minefield::generateMap(int x, int y) {
  // Plant mines
  int num_placed = 0;

  while (num_placed < num_mines) {
    const int r_x = asw::random::between(0, width - 1);
    const int r_y = asw::random::between(0, height - 1);

    auto& cell = cells.at(r_x).at(r_y);
    if (cell.getType() != 9 && (r_x != x || r_y != y)) {
      cell.setType(9);
      num_placed++;
    }
  }

  // Number based on surrounding mines
  const std::array<int, 8> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
  const std::array<int, 8> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      if (cells[i][t].getType() == 9) {
        continue;
      }

      int type = 0;
      for (int d = 0; d < 8; d++) {
        const int nx = i + dx[d];
        const int ny = t + dy[d];

        if (nx >= 0 && ny >= 0 && nx < width && ny < height &&
            cells[nx][ny].getType() == 9) {
          type++;
        }
      }

      cells[i][t].setType(type);
    }
  }
}

// Reveal some blocks recursively
int Minefield::reveal(float x, float y) {
  // Find cell position
  int cell_x;
  int cell_y;
  auto const* cell = getCellAt(x, y, &cell_x, &cell_y);

  // Flagged and revealed cells can not be clicked
  if (cell == nullptr || cell->isFlagged() || cell->isRevealed()) {
    return -1;
  }

  // Generate map on first click
  if (!first_reveal) {
    generateMap(cell_x, cell_y);
    first_reveal = true;
  }

  revealArea(cell_x, cell_y);

  return cell->getType();
}

// Reveal relative
void Minefield::revealArea(int x, int y) {
  // Surrounding cells
  const std::array<int, 8> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
  const std::array<int, 8> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

  // Stack for DFS
  std::stack<std::pair<int, int>> stack;
  stack.emplace(x, y);

  while (!stack.empty()) {
    auto [cx, cy] = stack.top();
    stack.pop();

    // Skip if out of bounds
    if (cx < 0 || cy < 0 || cx >= width || cy >= height) {
      continue;
    }

    Cell& cell = cells.at(cx).at(cy);

    // Skip if already revealed or flagged
    if (cell.isRevealed() || cell.isFlagged()) {
      continue;
    }

    // Reveal cell
    cell.reveal();

    // If cell is empty, reveal surrounding cells
    if (cell.getType() == 0) {
      for (size_t i = 0; i < dx.size(); i++) {
        stack.emplace(cx + dx.at(i), cy + dy.at(i));
      }
    }
  }
}

void Minefield::revealMap() {
  for (auto& row : cells) {
    for (auto& cell : row) {
      cell.reveal();
    }
  }
}

void Minefield::toggleFlag(float x, float y) {
  if (Cell* temp = getCellAt(x, y); temp != nullptr) {
    temp->toggleFlag();
  }
}

// Get cell at screen position
Cell* Minefield::getCellAt(float x, float y, int* pos_x, int* pos_y) {
  const auto position = asw::Vec2<float>(x, y);

  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      if (cells.at(i).at(t).transform.contains(position)) {
        if (pos_x != nullptr) {
          *pos_x = i;
        }

        if (pos_y != nullptr) {
          *pos_y = t;
        }

        return &cells.at(i).at(t);
      }
    }
  }

  return nullptr;
}

// Draw map
void Minefield::draw() {
  for (auto& row : cells) {
    for (auto& cell : row) {
      cell.draw();
    }
  }
}

// Draw map
void Minefield::update(float dt) {
  num_flagged = 0;
  num_unknown = 0;
  num_revealed = 0;

  for (auto& row : cells) {
    for (auto& cell : row) {
      cell.update(dt);

      if (cell.isFlagged()) {
        num_flagged++;
      } else if (cell.isRevealed()) {
        num_revealed++;
      } else {
        num_unknown++;
      }
    }
  }
}
