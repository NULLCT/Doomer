#pragma once

#include <SFML/Graphics.hpp>

class Chara {
private:
  const int size = 10;
  const int movespeed = 5;

  sf::CircleShape circle;

public:
  Chara();
  void update(sf::RenderWindow* _window);
};