
#include "app/application.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

#include "gfx/grid.h"

Application::Application(unsigned int winWidth, unsigned int winHeith)
    : window_width_(winWidth), window_height_(winHeith) {
  window_.setPosition(sf::Vector2i(500, 500));
  window_.create(sf::VideoMode(window_width_, window_height_), "Tic Tac Toe");
  LoadFonts();
}

void Application::InitPlayers(const sf::Texture& tex1,
                              const sf::Texture& tex2) {
  player1_.id_ = Player::ID::HUMAN;
  player2_.id_ = Player::ID::AI;
  if (drand48() < 0.5) {
    player1_.texture_ = tex1;
    player2_.texture_ = tex2;
  } else {
    player1_.texture_ = tex2;
    player2_.texture_ = tex1;
  }

  if (drand48() < 0.5) {
    player1_.state_ = Player::State::READY;
    player2_.state_ = Player::State::WAITING;
  } else {
    player1_.state_ = Player::State::WAITING;
    player2_.state_ = Player::State::READY;
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

      if (event.type == sf::Event::MouseButtonPressed) {
        if (player1_.state_ == Player::State::READY) {
          auto pixel_pos = sf::Mouse::getPosition(window_);
          auto coords = window_.mapPixelToCoords(pixel_pos);
          Cell* c = grid_.FindCellAtPos(coords);
          if (c) {
            if (IsPlayerMoveValid(*c)) {
              grid_.UpdateCell(*c, player1_);
              player1_.state_ = Player::State::WAITING;
              player2_.state_ = Player::State::READY;
            }
          }
        }
      }

      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 49 && event.text.unicode <= 57) {
          if (player2_.state_ == Player::State::READY) {
            int id = MapInputToGridId(event.text.unicode);
            Cell* c = grid_.FindCellById(id);
            if (c) {
              if (IsPlayerMoveValid(*c)) {
                grid_.UpdateCell(*c, player2_);
                player2_.state_ = Player::State::WAITING;
                player1_.state_ = Player::State::READY;
              }
            }
          }
        }
      }

      grid_.Draw(window_);
      grid_.DrawWiningLine(window_);

      if (DoesPlayerWin(player1_.id_)) {
        DisplayMessage("You Won!!!", fonts_.wining_msg_font_, sf::Color::Cyan);
      } else if (DoesPlayerWin(player2_.id_)) {
        DisplayMessage("Game Over!", fonts_.loosing_msg_font_, sf::Color::Red);
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

bool Application::IsPlayerMoveValid(const Cell& c) const {
  return c.id_ >= 1 && c.id_ <= 9 && c.state_ == Cell::State::EMPTY;
}

int Application::MapInputToGridId(char c) { return static_cast<int>(c - '0'); }

bool Application::DoesPlayerWin(const Player::ID& player_id) {
  return grid_.AnyTripletFor(player_id);
}

bool Application::LoadFonts() {
  if (!fonts_.wining_msg_font_.loadFromFile("../assets/chlorinr.ttf") ||
      !fonts_.loosing_msg_font_.loadFromFile("../assets/plasdrpe.ttf")) {
    // error
    return false;
  }
  return true;
}

void Application::DisplayMessage(const std::string& msg, const sf::Font& font,
                                 const sf::Color& c) {
  std::string message = msg;  //+ "Click or press enter to continue..";
  sf::Text text;
  text.setFont(font);
  text.setString(message);
  text.setCharacterSize(128);
  text.setFillColor(c);
  text.setPosition(0.f, window_.getSize().y / 3.f);
  window_.draw(text);
}
