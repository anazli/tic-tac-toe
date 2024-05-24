#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "app/player.h"

struct Cell {
  enum class State { EMPTY, FILLED };

  Cell() : state_(State::EMPTY), player_id_(Player::ID::NONE) {}
  bool CanBeUpdated(const sf::Vector2f& mousePos) const {
    return sprite_.getGlobalBounds().contains(mousePos) &&
           state_ == State::EMPTY;
  }

  State state_;
  sf::Sprite sprite_;
  unsigned int id_;
  Player::ID player_id_;
};
