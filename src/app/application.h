#pragma once

#include <SFML/Window.hpp>

class Application {
 public:
  Application(unsigned int winWidth = 800, unsigned int winHeight = 600);
  Application(const Application& other) = delete;
  Application& operator=(const Application& other) = delete;

  void RunMainLoop();

 private:
  void CreateWindow();

  sf::Window window_;
  unsigned int window_width_;
  unsigned int window_height_;
};
