#include "gfx/grid.h"

#include <cassert>

Grid::Grid(const sf::Vector2u& winSize, const sf::Vector2u& texSize,
           float lineThickness)
    : texture_size_(texSize), line_thickness_(lineThickness) {
  sf::Vector2f windowCenter = sf::Vector2f(winSize) / 2.f;
  origin_.x = windowCenter.x - 3.f * texSize.x / 2.f;
  origin_.y = windowCenter.y - 3.f * texSize.y / 2.f;
  ArrangeCells();
  CreateGridLines();
}

Cell& Grid::GetCellAt(unsigned int row, unsigned int col) {
  assert(row >= 0 && row < grid_size_.x);
  assert(col >= 0 && col < grid_size_.y);
  return cells_[row][col];
}

void Grid::Draw(sf::RenderWindow& window) {
  for (const auto& line : lines_) {
    window.draw(line);
  }
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      window.draw(cell.sprite_);
    }
  }
}

void Grid::UpdateCell(const sf::Vector2f& mousePos, const sf::Texture& tex) {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.CanBeUpdated(mousePos)) {
        cell.sprite_.setTexture(tex);
        cell.state_ = Cell::State::FILLED;
      }
    }
  }
}

void Grid::SetInitialStateOfCells(const sf::Texture& tex,
                                  const sf::Vector2f& scale) {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell.state_ = Cell::State::EMPTY;
      cell.sprite_.setTexture(tex);
      cell.sprite_.setScale(scale);
    }
  }
}

void Grid::ArrangeCells() {
  for (auto row = 0; row < grid_size_.x; ++row) {
    std::vector<Cell> cols;
    for (auto col = 0; col < grid_size_.y; ++col) {
      float x = origin_.x + texture_size_.x * col + line_thickness_;
      float y = origin_.y + texture_size_.y * row + line_thickness_;
      Cell c;
      c.sprite_.setPosition(sf::Vector2f(x, y));
      cols.emplace_back(c);
    }
    cells_.emplace_back(cols);
  }
}

void Grid::CreateGridLines() {
  lines_[0].setPosition(origin_.x, origin_.y + texture_size_.y);
  lines_[0].setSize(
      sf::Vector2f(texture_size_.x * cells_[0].size(), line_thickness_));

  lines_[1].setPosition(origin_.x, origin_.y + 2 * texture_size_.y);
  lines_[1].setSize(
      sf::Vector2f(texture_size_.x * cells_[0].size(), line_thickness_));

  lines_[2].setPosition(origin_.x + texture_size_.x, origin_.y);
  lines_[2].setSize(
      sf::Vector2f(line_thickness_, texture_size_.x * cells_.size()));

  lines_[3].setPosition(origin_.x + 2 * texture_size_.x, origin_.y);
  lines_[3].setSize(
      sf::Vector2f(line_thickness_, texture_size_.x * cells_.size()));
}
