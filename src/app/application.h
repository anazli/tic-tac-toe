#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include "app/player.h"
#include "gfx/grid.h"

class Application {
 public:
  Application(unsigned int winWidth = 800, unsigned int winHeight = 600);
  Application(const Application& other) = delete;
  Application& operator=(const Application& other) = delete;

  void InitPlayers(const sf::Texture& tex1, const sf::Texture& tex2);
  void InitGrid(const sf::Texture& tex);
  void RunMainLoop();

 private:
  bool IsPlayerMoveValid(const Cell& c) const;
  int MapInputToGridId(char c);
  bool DoesPlayerWin(const Player::ID& player_id);

  sf::RenderWindow window_;
  unsigned int window_width_;
  unsigned int window_height_;
  Grid grid_;
  Player player1_;
  Player player2_;
};
