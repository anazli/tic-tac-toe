#pragma once

#include <SFML/Graphics/Texture.hpp>

struct Player {
  enum class State { READY, WAITING };
  enum class ID { NONE, HUMAN, AI };
  Player() : state_(State::WAITING) {}

  sf::Texture texture_;
  State state_;
  ID id_;
};
