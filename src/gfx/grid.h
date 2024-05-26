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
  void DrawWiningLine(sf::RenderWindow& window);
  void UpdateCell(Cell& c, const Player& player);
  void SetInitialStateOfCells(const sf::Texture& tex,
                              const sf::Vector2f& scale);
  Cell* FindCellAtPos(sf::Vector2f& pos);
  Cell* FindCellById(unsigned int id);
  bool AnyTripletFor(const Player::ID& player_id);

 private:
  void ArrangeCells(const sf::Vector2u& texture_size, float line_thickness);
  void CreateStaticGridLines(const sf::Vector2u& texture_size,
                             float line_thickness);
  void CreateWiningLine(float x, float y, float rotation);

  const sf::Vector2u grid_size_ = sf::Vector2u(3, 3);
  sf::Vector2f origin_;
  std::vector<std::vector<Cell>> cells_;
  std::vector<sf::RectangleShape> lines_ = std::vector<sf::RectangleShape>(4);
  float line_length_;
  sf::RectangleShape final_line_;
};
