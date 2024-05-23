#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Cell {
  enum class State { EMPTY, FILLED };

  Cell() : state_(State::EMPTY) {}
  bool CanBeUpdated(const sf::Vector2f& mousePos) const {
    return sprite_.getGlobalBounds().contains(mousePos) &&
           state_ == State::EMPTY;
  }

  State state_;
  sf::Sprite sprite_;
};
