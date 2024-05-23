#include "gfx/cell.h"

Cell::Cell() : state_(State::EMPTY) { sprite_.setColor(sf::Color::Black); }

void Cell::SetTexture(const sf::Texture& tex) { sprite_.setTexture(tex); }

void Cell::SetPosition(const sf::Vector2f& pos) { sprite_.setPosition(pos); }

void Cell::SetState(const State& s) { state_ = s; }

Cell::State Cell::GetState() const { return state_; }

sf::Sprite& Cell::GetDrawable() { return sprite_; }

const sf::Sprite& Cell::GetDrawable() const { return sprite_; }

bool Cell::CanBeUpdated(const sf::Vector2f& mousePos) const {
  return sprite_.getGlobalBounds().contains(mousePos) && state_ == State::EMPTY;
}
