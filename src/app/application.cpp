
#include "app/application.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

#include "gfx/app_message.h"
#include "gfx/grid.h"

Application::Application(unsigned int window_width, unsigned int window_height)
    : m_player1(Player::ID::HUMAN), m_player2(Player::ID::AI) {
  m_window.setPosition(sf::Vector2i(500, 500));
  m_window.create(sf::VideoMode(window_width, window_height), "Tic Tac Toe");
}

void Application::InitPlayers(const sf::Texture& tex1,
                              const sf::Texture& tex2) {
  if (drand48() < 0.5) {
    m_player1.SetTexture(tex1);
    m_player2.SetTexture(tex2);
  } else {
    m_player1.SetTexture(tex2);
    m_player2.SetTexture(tex1);
  }

  if (drand48() < 0.5) {
    m_player1.SetState(Player::State::READY);
    m_player2.SetState(Player::State::WAITING);
  } else {
    m_player1.SetState(Player::State::WAITING);
    m_player2.SetState(Player::State::READY);
  }
}

void Application::InitGrid(const sf::Texture& tex) {
  GridParams params;
  params.window_size_ = m_window.getSize();
  params.default_tex_size_ = tex.getSize();
  params.line_thickness_ = 2.f;
  m_grid.Init(params);
  m_grid.SetInitialStateOfCells(tex, sf::Vector2f(0.99f, 0.99f));
}

void Application::RunMainLoop() {
  while (m_window.isOpen()) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }

      m_window.clear(sf::Color::Black);

      if (IsMoveDoneByPlayer(event)) {
        auto pixel_pos = sf::Mouse::getPosition(m_window);
        auto coords = m_window.mapPixelToCoords(pixel_pos);
        Cell* c = m_grid.FindCellAtPos(coords);
        if (IsPlayerMoveValid(c)) {
          m_grid.UpdateCell(*c, m_player1);
          m_player1.SetState(Player::State::WAITING);
          m_player2.SetState(Player::State::READY);
        }
      }

      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 49 && event.text.unicode <= 57) {
          if (m_player2.GetState() == Player::State::READY) {
            int id = MapInputToGridId(event.text.unicode);
            Cell* c = m_grid.FindCellById(id);
            if (IsPlayerMoveValid(c)) {
              m_grid.UpdateCell(*c, m_player2);
              m_player2.SetState(Player::State::WAITING);
              m_player1.SetState(Player::State::READY);
            }
          }
        }
      }

      m_grid.Draw(m_window);
      m_grid.DrawWiningLine(m_window);

      if (PlayerWins(m_player1.GetId())) {
        auto text = AppMessage(AppMessage::MsgType::VICTORY, sf::Color::Cyan)
                        .CreateMsg(m_window);
        m_window.draw(text);
      } else if (PlayerWins(m_player2.GetId())) {
        auto text = AppMessage(AppMessage::MsgType::DEFEAT, sf::Color::Red)
                        .CreateMsg(m_window);
        m_window.draw(text);
        // You lost (AI wins)
        // terminate or reset
      } else {
        // check if we have draw
        // terminate or reset
      }

      m_window.display();
    }
  }
}

bool Application::IsPlayerMoveValid(const Cell* c) const {
  return c && c->id >= 1 && c->id <= 9 && c->state == Cell::State::EMPTY;
}

int Application::MapInputToGridId(char c) { return static_cast<int>(c - '0'); }

bool Application::PlayerWins(const Player::ID& player_id) {
  return m_grid.AnyTripletFor(player_id);
}

bool Application::IsMoveDoneByPlayer(const sf::Event& event) {
  return event.type == sf::Event::MouseButtonPressed &&
         m_player1.GetState() == Player::State::READY;
}
