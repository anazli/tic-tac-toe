
#include "app/application.h"

#include <limits.h>
#include <unistd.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

#include "gfx/app_message.h"
#include "gfx/grid.h"

namespace {
const std::string APP_NAME = "Tic Tac Toe";
const std::string ASSET_FOLDER = "assets";
const std::string GRID_ASSET_NAME = "black.jpg";
const std::string CROSS_ASSET_NAME = "textureX.jpg";
const std::string CIRCLE_ASSET_NAME = "textureO.jpg";

static std::string FindAssetsDir() {
  namespace fs = std::filesystem;
  char buf[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  fs::path start;
  if (len != -1) {
    buf[len] = '\0';
    start = fs::path(buf).parent_path();
  } else {
    start = fs::current_path();
  }

  // walk up a few levels searching for an "assets" directory
  for (int i = 0; i < 10; ++i) {
    fs::path cand = start / ASSET_FOLDER;
    if (fs::exists(cand) && fs::is_directory(cand)) {
      return cand.string();
    }
    if (start.has_parent_path())
      start = start.parent_path();
    else
      break;
  }

  return std::string();
}
}  // namespace

Application::Application(unsigned int window_width, unsigned int window_height)
    : m_player1(Player::ID::HUMAN),
      m_player2(Player::ID::AI),
      m_game_state(GameState::FINISHED) {
  m_window.setPosition(sf::Vector2i(500, 500));
  m_window.create(sf::VideoMode(window_width, window_height), APP_NAME);

  std::string assets_dir = FindAssetsDir();
  if (assets_dir.empty()) {
    assets_dir = "./" + ASSET_FOLDER;
  }

  m_grid_tex.loadFromFile(assets_dir + "/" + GRID_ASSET_NAME);
  m_cross.loadFromFile(assets_dir + "/" + CROSS_ASSET_NAME);
  m_circle.loadFromFile(assets_dir + "/" + CIRCLE_ASSET_NAME);
  srand48(static_cast<long>(time(nullptr)));
}

void Application::InitPlayers() {
  if (drand48() < 0.5) {
    m_player1.SetTexture(m_cross);
    m_player2.SetTexture(m_circle);
  } else {
    m_player1.SetTexture(m_circle);
    m_player2.SetTexture(m_cross);
  }

  if (drand48() < 0.5) {
    m_player1.SetState(Player::State::READY);
    m_player2.SetState(Player::State::WAITING);
  } else {
    m_player1.SetState(Player::State::WAITING);
    m_player2.SetState(Player::State::READY);
  }
}

void Application::InitGrid() {
  GridParams params;
  params.window_size_ = m_window.getSize();
  params.default_tex_size_ = m_grid_tex.getSize();
  params.line_thickness_ = 2.f;
  m_grid.Init(params);
  m_grid.SetInitialStateOfCells(m_grid_tex, sf::Vector2f(0.99f, 0.99f));
}

void Application::RunMainLoop() {
  InitPlayers();
  InitGrid();
  m_game_state = GameState::RUNNING;

  while (m_window.isOpen()) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
        return;
      }
    }
    ProcessGameLogic();
    RenderFrame();
  }
}

void Application::ProcessGameLogic() {
  if (m_game_state == GameState::FINISHED) {
    InitPlayers();
    InitGrid();
    m_game_state = GameState::RUNNING;
    return;
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
      m_player1.GetState() == Player::State::READY) {
    auto pixel_pos = sf::Mouse::getPosition(m_window);
    auto coords = m_window.mapPixelToCoords(pixel_pos);
    Cell* c = m_grid.FindCellAtPos(coords);
    if (IsPlayerMoveValid(c)) {
      m_grid.UpdateCell(*c, m_player1);
      m_player1.SetState(Player::State::WAITING);
      m_player2.SetState(Player::State::READY);
    }
  }
}

void Application::RenderFrame() {
  m_window.clear(sf::Color::Black);

  m_grid.Draw(m_window);
  m_grid.DrawWiningLine(m_window);
  sf::Text text;

  if (PlayerWins(m_player1.GetId())) {
    text = AppMessage(AppMessage::MsgType::VICTORY, sf::Color::Cyan)
               .CreateMsg(m_window);
    m_game_state = GameState::FINISHED;
  } else if (PlayerWins(m_player2.GetId())) {
    text = AppMessage(AppMessage::MsgType::DEFEAT, sf::Color::Red)
               .CreateMsg(m_window);
    m_game_state = GameState::FINISHED;
  }
  m_window.draw(text);
  m_window.display();
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
