#include "gfx/grid.h"

Grid::Grid(const sf::Vector2u& gridSize, const sf::Vector2u& winSize,
           const sf::Vector2u& texSize)
    : grid_size_(gridSize), texture_size_(texSize) {
  sf::Vector2f windowCenter = sf::Vector2f(winSize) / 2.f;
  origin_.x = windowCenter.x - 3.f * texSize.x / 2.f;
  origin_.y = windowCenter.y - 3.f * texSize.y / 2.f;
  ArrangeCells();
  CreateLines();
}

Cell& Grid::GetCellAt(unsigned int row, unsigned int col) {
  return cells_[row][col];
}

void Grid::Draw(sf::RenderWindow& window) {
  for (const auto& line : lines_) {
    window.draw(line);
  }
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      window.draw(cell.GetDrawable());
    }
  }
}

void Grid::ArrangeCells() {
  for (auto row = 1; row <= grid_size_.x; ++row) {
    std::vector<Cell> cols;
    for (auto col = 1; col <= grid_size_.y; ++col) {
      float x = origin_.x * col;
      float y = origin_.y * row;
      Cell c;
      c.SetPosition(sf::Vector2f(x, y));
      cols.emplace_back(c);
    }
    cells_.emplace_back(cols);
  }
}

void Grid::CreateLines() {
  lines_[0].setPosition(origin_.x, origin_.y + texture_size_.y);
  lines_[0].setSize(sf::Vector2f(texture_size_.x * cells_[0].size(), 1.f));

  lines_[1].setPosition(origin_.x, origin_.y + 2 * texture_size_.y);
  lines_[1].setSize(sf::Vector2f(texture_size_.x * cells_[0].size(), 1.f));

  lines_[2].setPosition(origin_.x + texture_size_.x, origin_.y);
  lines_[2].setSize(sf::Vector2f(1.f, texture_size_.x * cells_.size()));

  lines_[3].setPosition(origin_.x + 2 * texture_size_.x, origin_.y);
  lines_[3].setSize(sf::Vector2f(1.f, texture_size_.x * cells_.size()));
}
