#pragma once

#include <SFML/Graphics.hpp>

struct LineSeg{
  sf::Vector2f begin, end;

  LineSeg(const sf::Vector2f& _begin, const sf::Vector2f& _end) {
    begin = _begin;
    end = _end;
  }
};