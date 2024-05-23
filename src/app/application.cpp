
#include "app/application.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "gfx/grid.h"

Application::Application(unsigned int winWidth, unsigned int winHeith)
    : window_width_(winWidth), window_height_(winHeith) {}

void Application::RunMainLoop() {
  CreateWindow();
  sf::Texture texX;
  if (!texX.loadFromFile("../assets/textureX.jpg")) {
    // Error
  }
  sf::Texture texBlack;
  if (!texBlack.loadFromFile("../assets/black.jpg")) {
    // Error
  }
  Grid grid(window_.getSize(), texBlack.getSize(), 2.f);
  grid.SetInitialStateOfCells(texBlack, sf::Vector2f(0.99f, 0.99f));
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        auto pos = sf::Mouse::getPosition(window_);
        auto transfPos = window_.mapPixelToCoords(pos);
        grid.UpdateCell(transfPos, texX);
      }
      window_.clear(sf::Color::Black);  // todo: might not be necessary
      /***********************
       * draw logic here
       * *********************/
      grid.Draw(window_);
      window_.display();
    }
  }
}

void Application::CreateWindow() {
  window_.setPosition(sf::Vector2i(500, 500));
  window_.create(sf::VideoMode(window_width_, window_height_), "Tic Tac Toe");
}
