
#include "app/application.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "gfx/grid.h"

Application::Application(unsigned int winWidth, unsigned int winHeith)
    : window_width_(winWidth), window_height_(winHeith) {}

void Application::RunMainLoop() {
  CreateWindow();
  sf::Texture tex;
  if (!tex.loadFromFile("../assets/textureX.jpg")) {
    // Error
  }
  Grid grid(sf::Vector2u(3, 3), window_.getSize(), tex.getSize());
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
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
