#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class CheckConflict {
private:
  vector<sf::RectangleShape> rects;
  vector<bool> trs;

public:

  void setSize(int _size) {
    rects.resize(_size);
    trs.resize(_size);
  }

  CheckConflict(int _size) {
    setSize(_size);
  }

  void update(sf::RenderWindow* _window, vector<sf::VertexArray>* rays, vector<sf::VertexArray>* walls, sf::Vector2f _charapos, int _raylength) {
    for (auto& tr : trs)
      tr = false;

    for (auto& wall : *walls) {
      int viewcnt = 1;
      for (auto& ray : *rays) {
        /*
          ray[0].pos => ray[1].posw
          wall[0].pos => wall[1].pos
        */

        double raytilt = (ray[0].position.y - ray[1].position.y) / (ray[0].position.x - ray[1].position.x);
        double rayadd = ray[0].position.y - (ray[0].position.x * raytilt);
        double walltilt = (wall[0].position.y - wall[1].position.y) / (wall[0].position.x - wall[1].position.x);
        double walladd = wall[0].position.y - (wall[0].position.x * walltilt);

        double crossxpos = (rayadd - walladd) / -(raytilt - walltilt);
        double crossypos = (crossxpos * raytilt) + rayadd;

        if (isinf(raytilt)) {
          crossxpos = ray[0].position.x;
          crossypos = (crossxpos * walltilt) + walladd;
        }

        //draw conflict pos
        if ((wall[0].position.x <= crossxpos && crossxpos <= wall[1].position.x) || (wall[1].position.x <= crossxpos && crossxpos <= wall[0].position.x)) {
          if ((ray[0].position.x <= crossxpos && crossxpos <= ray[1].position.x) || (ray[1].position.x <= crossxpos && crossxpos <= ray[0].position.x)) {

            double lengthfromchara = sqrt(pow(crossxpos - _charapos.x, 2) + pow(crossypos - _charapos.y, 2));

            if (trs[viewcnt - 1]) {
              if (rects[viewcnt - 1].getSize().y > (_raylength - lengthfromchara)) {
                viewcnt++;
                continue;
              }
            }
            else {
              trs[viewcnt - 1] = true;
            }

            constexpr int size = 5;
            sf::CircleShape circle(size);
            circle.setOrigin(size, size);
            circle.setPosition(crossxpos, crossypos);
            _window->draw(circle);

            sf::RectangleShape rect;
            rects[viewcnt - 1].setSize(sf::Vector2f(1000 / rays->size(), (_raylength - lengthfromchara)));
            rects[viewcnt - 1].setPosition(sf::Vector2f(2000 - (viewcnt * (1000 / rays->size())), 100 + (lengthfromchara) / 2));
            rects[viewcnt - 1].setFillColor(sf::Color((1 - lengthfromchara / double(_raylength)) * 255, (1 - lengthfromchara / double(_raylength)) * 255, (1 - lengthfromchara / double(_raylength)) * 255));
          }
        }

        viewcnt++;
      }
    }

    for (int i = 0; i < rects.size(); i++) {
      if(trs[i])
        _window->draw(rects[i]);
    }
  }

};