#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "chara.hpp"
#include "rays.hpp"
#include "walls.hpp"

using namespace std;

void checkConflictAndDraw(sf::RenderWindow *_window, vector<sf::VertexArray>* rays, vector<sf::VertexArray>* walls,sf::Vector2f _charapos,int _raylength) {
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
          constexpr int size = 5;
          sf::CircleShape circle(size);
          circle.setOrigin(size, size);
          circle.setPosition(crossxpos, crossypos);
          _window->draw(circle);

          double lengthfromchara = sqrt(pow(crossxpos - _charapos.x, 2) + pow(crossypos - _charapos.y, 2));
          sf::RectangleShape rect;
          rect.setSize(sf::Vector2f(1000 / rays->size(), (_raylength - lengthfromchara)));
          rect.setPosition(sf::Vector2f(2000 - (viewcnt * (1000 / rays->size())), 100 + (lengthfromchara)/2));
          rect.setFillColor(sf::Color((1 - lengthfromchara / double(_raylength)) * 255, (1- lengthfromchara / double(_raylength)) * 255, (1 -lengthfromchara / double(_raylength)) * 255));
          _window->draw(rect);
        }
      }

      viewcnt++;
    }
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);

  Chara chara;
  Rays rays(64, 256);
  Walls walls;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      }
    } 
    window.clear();

    chara.update(&window);
    rays.update(&window, chara.getPosition());
    walls.update(&window);
    checkConflictAndDraw(&window,rays.getRays(), walls.getWalls(),chara.getPosition(),rays.getRayLength());

    window.display();
  }
}
