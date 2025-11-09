#include "gfx/app_message.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace {
const std::string YOU_WON_TEXT = "You Won!!!";
const std::string GAME_OVER_TEXT = "Game Over!";
}  // namespace

AppMessage::AppMessage(MsgType msg_type, const sf::Color& msg_color,
                       unsigned int char_size)
    : m_msg_type(msg_type), m_msg_color(msg_color), m_charSize(char_size) {
  if (msg_type == VICTORY) {
    m_font.loadFromFile("../assets/chlorinr.ttf");
  } else if (msg_type == DEFEAT) {
    m_font.loadFromFile("../assets/plasdrpe.ttf");
  }
}

sf::Text AppMessage::CreateMsg(const sf::RenderWindow& window) {
  sf::Font font;
  sf::Text text;
  auto msg = m_msg_type == VICTORY ? YOU_WON_TEXT : GAME_OVER_TEXT;
  text.setFont(font);
  text.setString(msg);
  text.setCharacterSize(m_charSize);
  text.setFillColor(m_msg_color);
  text.setPosition(0.f, window.getSize().y / 3.f);
  return text;
}