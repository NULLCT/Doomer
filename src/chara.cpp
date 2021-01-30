#include "chara.hpp"

Chara::Chara() : circle(size) {
  circle.setFillColor(sf::Color::White);
}

void Chara::update(sf::RenderWindow* _window) {
  //key action
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    circle.setPosition(circle.getPosition() + sf::Vector2f(0, -movespeed));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    circle.setPosition(circle.getPosition() + sf::Vector2f(0, movespeed));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    circle.setPosition(circle.getPosition() + sf::Vector2f(-movespeed, 0));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    circle.setPosition(circle.getPosition() + sf::Vector2f(movespeed, 0));

  _window->draw(circle);
}
