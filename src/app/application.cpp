
#include "app/application.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

#include "gfx/app_message.h"
#include "gfx/grid.h"

Application::Application(unsigned int winWidth, unsigned int winHeith)
    : window_width_(winWidth),
      window_height_(winHeith),
      player1_(Player::ID::HUMAN),
      player2_(Player::ID::AI) {
  window_.setPosition(sf::Vector2i(500, 500));
  window_.create(sf::VideoMode(window_width_, window_height_), "Tic Tac Toe");
}

void Application::InitPlayers(const sf::Texture& tex1,
                              const sf::Texture& tex2) {
  if (drand48() < 0.5) {
    player1_.SetTexture(tex1);
    player2_.SetTexture(tex2);
  } else {
    player1_.SetTexture(tex2);
    player2_.SetTexture(tex1);
  }

  if (drand48() < 0.5) {
    player1_.SetState(Player::State::READY);
    player2_.SetState(Player::State::WAITING);
  } else {
    player1_.SetState(Player::State::WAITING);
    player2_.SetState(Player::State::READY);
  }
}

void Application::InitGrid(const sf::Texture& tex) {
  GridParams params;
  params.window_size_ = window_.getSize();
  params.default_tex_size_ = tex.getSize();
  params.line_thickness_ = 2.f;
  grid_.Init(params);
  grid_.SetInitialStateOfCells(tex, sf::Vector2f(0.99f, 0.99f));
}

void Application::RunMainLoop() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }

      window_.clear(sf::Color::Black);

      if (IsMoveDoneByPlayer(event)) {
        auto pixel_pos = sf::Mouse::getPosition(window_);
        auto coords = window_.mapPixelToCoords(pixel_pos);
        Cell* c = grid_.FindCellAtPos(coords);
        if (IsPlayerMoveValid(c)) {
          grid_.UpdateCell(*c, player1_);
          player1_.SetState(Player::State::WAITING);
          player2_.SetState(Player::State::READY);
        }
      }

      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 49 && event.text.unicode <= 57) {
          if (player2_.GetState() == Player::State::READY) {
            int id = MapInputToGridId(event.text.unicode);
            Cell* c = grid_.FindCellById(id);
            if (IsPlayerMoveValid(c)) {
              grid_.UpdateCell(*c, player2_);
              player2_.SetState(Player::State::WAITING);
              player1_.SetState(Player::State::READY);
            }
          }
        }
      }

      grid_.Draw(window_);
      grid_.DrawWiningLine(window_);

      if (PlayerWins(player1_.GetId())) {
        auto text = AppMessage(AppMessage::MsgType::VICTORY, sf::Color::Cyan)
                        .CreateMsg(window_);
        window_.draw(text);
      } else if (PlayerWins(player2_.GetId())) {
        auto text = AppMessage(AppMessage::MsgType::DEFEAT, sf::Color::Red)
                        .CreateMsg(window_);
        window_.draw(text);
        // You lost (AI wins)
        // terminate or reset
      } else {
        // check if we have draw
        // terminate or reset
      }

      window_.display();
    }
  }
}

bool Application::IsPlayerMoveValid(const Cell* c) const {
  return c && c->id >= 1 && c->id <= 9 && c->state == Cell::State::EMPTY;
}

int Application::MapInputToGridId(char c) { return static_cast<int>(c - '0'); }

bool Application::PlayerWins(const Player::ID& player_id) {
  return grid_.AnyTripletFor(player_id);
}

bool Application::IsMoveDoneByPlayer(const sf::Event& event) {
  return event.type == sf::Event::MouseButtonPressed &&
         player1_.GetState() == Player::State::READY;
}
