#include "gfx/grid.h"

void Grid::Init(const GridParams& params) {
  sf::Vector2f windowCenter = sf::Vector2f(params.window_size_) / 2.f;
  origin_.x = windowCenter.x - 3.f * params.default_tex_size_.x / 2.f;
  origin_.y = windowCenter.y - 3.f * params.default_tex_size_.y / 2.f;
  ArrangeCells(params.default_tex_size_, params.line_thickness_);
  line_length_ = params.default_tex_size_.x * cells_.size();
  CreateStaticGridLines(params.default_tex_size_, params.line_thickness_);
}

void Grid::Draw(sf::RenderWindow& window) {
  for (const auto& line : lines_) {
    window.draw(line);
  }
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      window.draw(cell.sprite);
    }
  }
}

void Grid::DrawWiningLine(sf::RenderWindow& window) {
  window.draw(final_line_);
}

void Grid::UpdateCell(Cell& c, const Player& player) {
  c.sprite.setTexture(player.texture_);
  c.state = Cell::State::FILLED;
  c.player_id = player.id_;
}

void Grid::SetInitialStateOfCells(const sf::Texture& tex,
                                  const sf::Vector2f& scale) {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell.state = Cell::State::EMPTY;
      cell.sprite.setTexture(tex);
      cell.sprite.setScale(scale);
    }
  }
}

Cell* Grid::FindCellAtPos(sf::Vector2f& pos) {
  Cell* c = nullptr;
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.sprite.getGlobalBounds().contains(pos)) {
        c = &cell;
        break;
      }
    }
  }
  return c;
}

Cell* Grid::FindCellById(unsigned int id) {
  Cell* c = nullptr;
  for (auto& row : cells_) {
    for (auto& cell : row) {
      if (cell.id == id) {
        c = &cell;
        break;
      }
    }
  }
  return c;
}

bool Grid::AnyTripletFor(const Player::ID& player_id) {
  for (const auto& row : cells_) {
    if (row[0].player_id == player_id && row[1].player_id == player_id &&
        row[2].player_id == player_id) {
      Cell c(row[0]);
      CreateWiningLine(
          c.sprite.getPosition().x,
          c.sprite.getPosition().y + c.sprite.getGlobalBounds().height / 2.f,
          0.f);
      return true;
    }
  }

  for (int col = 0; col < cells_.size(); ++col) {
    if (cells_[0][col].player_id == player_id &&
        cells_[1][col].player_id == player_id &&
        cells_[2][col].player_id == player_id) {
      Cell c(cells_[0][col]);
      CreateWiningLine(
          c.sprite.getPosition().x + c.sprite.getGlobalBounds().width / 2.f,
          c.sprite.getPosition().y, 90.f);
      return true;
    }
  }

  if (cells_[0][0].player_id == player_id &&
      cells_[1][1].player_id == player_id &&
      cells_[2][2].player_id == player_id) {
    Cell c(cells_[0][0]);
    sf::Vector2f pos(c.sprite.getGlobalBounds().getPosition().x,
                     c.sprite.getGlobalBounds().getPosition().y);
    float offset = c.sprite.getGlobalBounds().width / 2.f;
    CreateWiningLine(pos.x + offset, pos.y + offset, 45.f);
    return true;
  }

  if (cells_[0][2].player_id == player_id &&
      cells_[1][1].player_id == player_id &&
      cells_[2][0].player_id == player_id) {
    Cell c(cells_[2][0]);
    sf::Vector2f pos(c.sprite.getGlobalBounds().left,
                     c.sprite.getGlobalBounds().getPosition().y);
    float offset = c.sprite.getGlobalBounds().height;
    CreateWiningLine(pos.x + offset / 2.f, pos.y + offset / 2.f, -45.f);
    return true;
  }
  return false;
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
      c.sprite.setPosition(sf::Vector2f(x, y));
      c.id = cell_id++;
      cols.emplace_back(c);
    }
    cells_.emplace_back(cols);
  }
}

void Grid::CreateStaticGridLines(const sf::Vector2u& texture_size,
                                 float line_thickness) {
  lines_[0].setPosition(origin_.x, origin_.y + texture_size.y);
  lines_[0].setSize(sf::Vector2f(line_length_, line_thickness));

  lines_[1].setPosition(origin_.x, origin_.y + 2 * texture_size.y);
  lines_[1].setSize(sf::Vector2f(line_length_, line_thickness));

  lines_[2].setPosition(origin_.x + texture_size.x, origin_.y);
  lines_[2].setSize(sf::Vector2f(line_thickness, line_length_));

  lines_[3].setPosition(origin_.x + 2 * texture_size.x, origin_.y);
  lines_[3].setSize(sf::Vector2f(line_thickness, line_length_));
}

void Grid::CreateWiningLine(float x, float y, float rotation) {
  final_line_.setPosition(x, y);
  final_line_.setSize(sf::Vector2f(line_length_, 5.f));
  final_line_.setRotation(rotation);
  final_line_.setFillColor(sf::Color::Red);
}
