#pragma once

#include <SFML/Graphics.hpp>

class Chara {
private:
  int size = 10; // chara size
  int movespeed = 5; // chara move speed


  sf::CircleShape circle;

public:
  Chara() : circle(size) {
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(size, size);
  }

  void update(sf::RenderWindow* _window) {
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

  sf::Vector2f getPosition() {
    return circle.getPosition();
  }
};
