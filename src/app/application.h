#pragma once

#include <SFML/Window.hpp>

class Application {
 public:
  Application(int winWidth = 800, int winHeight = 600);
  Application(const Application& other) = delete;
  Application& operator=(const Application& other) = delete;

  void RunMainLoop();

 private:
  void CreateWindow();

  sf::Window window_;
  int window_width_;
  int window_height_;
};
