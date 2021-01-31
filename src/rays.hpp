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

public:
  Rays(int _laynum, int _laylength) : ray(_laynum,sf::VertexArray(sf::LineStrip,2)) {
    laynum = _laynum;
    laylength = _laylength;
  }

  void update(sf::RenderWindow* _window, const sf::Vector2f& _charapos) {
    //set direction
    double direction = atan2(sf::Mouse::getPosition(*_window).y - _charapos.y, sf::Mouse::getPosition(*_window).x - _charapos.x);

    float angle = direction - M_PI / 2;

    for (int i = 0; i < laynum; i++) {
      angle += M_PI / (laynum+1);
      ray[i][0] = sf::Vector2f(_charapos);
      ray[i][1] = sf::Vector2f(_charapos) + sf::Vector2f(cos(angle) * laylength, sin(angle) * laylength);

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
