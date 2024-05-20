#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "gfx/cell.h"

class Grid {
 public:
  Grid(const sf::Vector2u& winSize, const sf::Vector2u& texSize);

  Cell& GetCellAt(unsigned int row, unsigned int col);
  void Draw(sf::RenderWindow& window);

 private:
  void ArrangeCells();
  void CreateGridLines(float thickness);

  const sf::Vector2u grid_size_ = sf::Vector2u(3, 3);

  sf::Vector2u texture_size_;
  sf::Vector2f origin_;
  std::vector<std::vector<Cell>> cells_;
  std::vector<sf::RectangleShape> lines_ = std::vector<sf::RectangleShape>(4);
};
