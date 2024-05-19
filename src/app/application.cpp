#include "app/application.h"

Application::Application(int winWidth, int winHeith)
    : window_width_(winWidth), window_height_(winHeith) {}

void Application::RunMainLoop() {
  CreateWindow();
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }
  }
}

void Application::CreateWindow() {
  window_.create(sf::VideoMode(window_width_, window_height_), "Tic Tac Toe");
}
