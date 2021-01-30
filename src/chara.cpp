#include "chara.hpp"

Chara::Chara() : circle(size) {
  circle.setFillColor(sf::Color::White);
  circle.setOrigin(size,size);
}

void Chara::update(sf::RenderWindow* _window) {
  //key action
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    circle.setPosition(circle.getPosition() + sf::Vector2f(0, -movespeed));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    circle.setPosition(circle.getPosition() + sf::Vector2f(0, movespeed));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    circle.setPosition(circle.getPosition() + sf::Vector2f(-movespeed, 0));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    circle.setPosition(circle.getPosition() + sf::Vector2f(movespeed, 0));

  _window->draw(circle);
}

sf::Vector2f Chara::getPosition() {
  return circle.getPosition();
}
