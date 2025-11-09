#include "app/player.h"
#include "player.h"

Player::Player(const ID& id): m_state(State::WAITING), m_id(id)  {

}

Player::ID Player::GetId() const { return m_id; }

void Player::SetTexture(const sf::Texture& texture) { m_texture = texture; }

sf::Texture Player::GetTexture() const { return m_texture; }

void Player::SetState(const State& state) {
    m_state = state;
}

Player::State Player::GetState() const { return m_state; }
