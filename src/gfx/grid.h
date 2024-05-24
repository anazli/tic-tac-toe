#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "app/player.h"
#include "gfx/cell.h"

struct GridParams {
  sf::Vector2u window_size_;
  sf::Vector2u default_tex_size_;
  float line_thickness_ = 2.f;
};

class Grid {
 public:
  void Init(const GridParams& params);
  void Draw(sf::RenderWindow& window);
  void UpdateCell(unsigned int id, const Player& player);
  void SetInitialStateOfCells(const sf::Texture& tex,
                              const sf::Vector2f& scale);
  Cell FindCellAt(const sf::Vector2f& pos) const;
  Cell FindCellById(unsigned int id);

 private:
  void ArrangeCells(const sf::Vector2u& texture_size, float line_thickness);
  void CreateGridLines(const sf::Vector2u& texture_size, float line_thickness);

  const sf::Vector2u grid_size_ = sf::Vector2u(3, 3);
  sf::Vector2f origin_;
  std::vector<std::vector<Cell>> cells_;
  std::vector<sf::RectangleShape> lines_ = std::vector<sf::RectangleShape>(4);
};
