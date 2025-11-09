#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "app/player.h"

struct Cell {
  enum class State { EMPTY, FILLED };

  Cell() : state(State::EMPTY), player_id(Player::ID::NONE) {}
  bool CanBeUpdated(const sf::Vector2f& mousePos) const {
    return sprite.getGlobalBounds().contains(mousePos) &&
           state == State::EMPTY;
  }

  State state;
  sf::Sprite sprite;
  unsigned int id;
  Player::ID player_id;
};
