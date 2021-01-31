#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Rays {
private:
  int laynum;
  int laylength;

  vector<sf::VertexArray> ray;

  float getRadianFromAngle(const float& _angle) {
    return _angle * (M_PI / 180);
  }

public:
  Rays(int _laynum, int _laylength) : ray(_laynum,sf::VertexArray(sf::LineStrip,2)) {
    laynum = _laynum;
    laylength = _laylength;
  }

  void update(sf::RenderWindow* _window, const sf::Vector2f& _pos) {
    float angle = 0;

    for (int i = 0; i < laynum; i++) {
      angle += 180.f / (laynum + 1);
      ray[i][0] = sf::Vector2f(_pos);
      ray[i][1] = sf::Vector2f(_pos) + sf::Vector2f(sf::Vector2f(cos(getRadianFromAngle(angle)) * laylength, -sin(getRadianFromAngle(angle)) * laylength));

      _window->draw(ray[i]);
    }
  }

  vector<sf::VertexArray> *getRays() {
    return &ray;
  }

  int getRayLength() {
    return laylength;
  }
};
