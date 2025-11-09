#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include "app/player.h"
#include "gfx/grid.h"

class Application {
 public:
  Application(unsigned int window_width = 800,
              unsigned int window_height = 600);
  Application(const Application& other) = delete;
  Application& operator=(const Application& other) = delete;

  void InitPlayers(const sf::Texture& tex1, const sf::Texture& tex2);
  void InitGrid(const sf::Texture& tex);
  void RunMainLoop();

 private:
  bool IsPlayerMoveValid(const Cell* c) const;
  int MapInputToGridId(char c);
  bool PlayerWins(const Player::ID& player_id);
  bool IsMoveDoneByPlayer(const sf::Event& event);

  sf::RenderWindow m_window;
  Grid m_grid;
  Player m_player1;
  Player m_player2;
};
