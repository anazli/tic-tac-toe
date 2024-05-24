#include "gfx/grid.h"

#include <cassert>

void Grid::Init(const GridParams& params) {
  sf::Vector2f windowCenter = sf::Vector2f(params.window_size_) / 2.f;
  origin_.x = windowCenter.x - 3.f * params.default_tex_size_.x / 2.f;
  origin_.y = windowCenter.y - 3.f * params.default_tex_size_.y / 2.f;
  ArrangeCells(params.default_tex_size_, params.line_thickness_);
  CreateGridLines(params.default_tex_size_, params.line_thickness_);
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

void Grid::UpdateCell(unsigned int id, const Player& player) {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.id_ == id) {
        cell.sprite_.setTexture(player.texture_);
        cell.state_ = Cell::State::FILLED;
        cell.player_id_ = player.id_;
        break;
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

Cell Grid::FindCellAt(const sf::Vector2f& pos) const {
  Cell c;
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.sprite_.getGlobalBounds().contains(pos)) {
        c = cell;
        break;
      }
    }
  }
  return c;
}

Cell Grid::FindCellById(unsigned int id) {
  Cell c;
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.id_ == id) {
        c = cell;
        break;
      }
    }
  }
  return c;
}

void Grid::ArrangeCells(const sf::Vector2u& texture_size,
                        float line_thickness) {
  unsigned int cell_id = 1;
  for (auto row = 0; row < grid_size_.x; ++row) {
    std::vector<Cell> cols;
    for (auto col = 0; col < grid_size_.y; ++col) {
      float x = origin_.x + texture_size.x * col + line_thickness;
      float y = origin_.y + texture_size.y * row + line_thickness;
      Cell c;
      c.sprite_.setPosition(sf::Vector2f(x, y));
      c.id_ = cell_id++;
      cols.emplace_back(c);
    }
    cells_.emplace_back(cols);
  }
}

void Grid::CreateGridLines(const sf::Vector2u& texture_size,
                           float line_thickness) {
  lines_[0].setPosition(origin_.x, origin_.y + texture_size.y);
  lines_[0].setSize(
      sf::Vector2f(texture_size.x * cells_[0].size(), line_thickness));

  lines_[1].setPosition(origin_.x, origin_.y + 2 * texture_size.y);
  lines_[1].setSize(
      sf::Vector2f(texture_size.x * cells_[0].size(), line_thickness));

  lines_[2].setPosition(origin_.x + texture_size.x, origin_.y);
  lines_[2].setSize(
      sf::Vector2f(line_thickness, texture_size.x * cells_.size()));

  lines_[3].setPosition(origin_.x + 2 * texture_size.x, origin_.y);
  lines_[3].setSize(
      sf::Vector2f(line_thickness, texture_size.x * cells_.size()));
}
