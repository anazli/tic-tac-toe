#pragma once

#include <SFML/Graphics/Texture.hpp>

class Player {
 public:
  enum State { READY, WAITING };
  enum ID { NONE, HUMAN, AI };
  Player(const ID& id);

  ID GetId() const;
  void SetTexture(const sf::Texture& texture);
  sf::Texture GetTexture() const;
  void SetState(const State& state);
  Player::State GetState() const;

 private:
  sf::Texture m_texture;
  Player::State m_state;
  ID m_id;
};
