#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
class RenderWindow;
}

class AppMessage {
 public:
  enum MsgType { VICTORY, DEFEAT };

  AppMessage(MsgType msg_type, const sf::Color& msg_color,
             unsigned int char_size = 128);

  sf::Text CreateMsg(const sf::RenderWindow& window);

 private:
  MsgType m_msg_type;
  sf::Color m_msg_color;
  unsigned int m_charSize;
  sf::Font m_font;
};