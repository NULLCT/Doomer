#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "lineseg.hpp"

using namespace std;

class Rays {
private:
  int laynum;
  int laylength;

  vector<LineSeg> ray;
  vector<sf::Vertex[2]> raylines;

  float getRadianFromAngle(const float& _angle) {
    return _angle * (M_PI / 180);
  }
public:
  Rays(int _laynum,int _laylength) : ray(_laynum) ,raylines(_laynum) {
    laynum = _laynum;
    laylength = _laylength;
  }

  void update(sf::RenderWindow *_window,const sf::Vector2f &_pos) {
    float angle = 0;

    for (int i = 0; i < laynum;i++) {
      angle += 180.f / (laynum + 1);
      ray[i].begin = sf::Vector2f(_pos);
      ray[i].end = ray[i].begin + sf::Vector2f(sf::Vector2f(cos(getRadianFromAngle(angle)) * laylength, -sin(getRadianFromAngle(angle)) * laylength));

      raylines[i][0] = ray[i].begin;
      raylines[i][1] = ray[i].end;
        
      _window->draw(raylines[i], 2, sf::Lines);
    }
  }

};