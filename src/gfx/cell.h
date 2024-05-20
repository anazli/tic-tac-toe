#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Cell {
 public:
  enum class State { EMPTY, FILLED };

  Cell() = default;
  void SetTexture(const sf::Texture& tex);
  void SetPosition(const sf::Vector2f& pos);
  void SetState(const State& s);
  State GetState() const;
  const sf::Sprite& GetDrawable() const;

 private:
  State state_;
  sf::Sprite sprite_;
};
