#include "app/application.h"

int main() {
  sf::Texture black_tex;
  if (!black_tex.loadFromFile("../assets/black.jpg")) {
    // Error
  }

  sf::Texture texX;
  if (!texX.loadFromFile("../assets/textureX.jpg")) {
    // Error
  }

  sf::Texture texO;
  if (!texO.loadFromFile("../assets/textureO.jpg")) {
    // Error
  }

  Application app;
  app.InitPlayers(texX, texO);
  app.InitGrid(black_tex);
  app.RunMainLoop();
  return 0;
}
