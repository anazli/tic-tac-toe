#include "gfx/cell.h"

void Cell::SetTexture(const sf::Texture& tex) { sprite_.setTexture(tex); }

void Cell::SetPosition(const sf::Vector2f& pos) { sprite_.setPosition(pos); }

void Cell::SetState(const State& s) { state_ = s; }

Cell::State Cell::GetState() const { return state_; }

const sf::Sprite& Cell::GetDrawable() const { return sprite_; }
