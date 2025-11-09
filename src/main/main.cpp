#include "app/application.h"

int main() {
  Application app;
  app.InitPlayers();
  app.InitGrid();
  app.RunMainLoop();
  return 0;
}
