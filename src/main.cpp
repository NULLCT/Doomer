#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "chara.hpp"
#include "rays.hpp"
#include "walls.hpp"

using namespace std;

void checkConflictAndDraw(sf::RenderWindow *_window, vector<sf::VertexArray>* rays, vector<sf::VertexArray>* walls) {
  for (auto& ray : *rays) for(auto &wall:*walls) {
    /*
      ray[0].pos => ray[1].posw
      wall[0].pos => wall[1].pos
    */

    double raytilt = (ray[0].position.y - ray[1].position.y) / (ray[0].position.x - ray[1].position.x);
    double rayadd = ray[0].position.y - (ray[0].position.x * raytilt);
    double walltilt = (wall[0].position.y - wall[1].position.y) / (wall[0].position.x - wall[1].position.x);
    double walladd = wall[0].position.y - (wall[0].position.x * walltilt);

    double crossxpos =  (rayadd - walladd) / -(raytilt - walltilt);
    double crossypos = (crossxpos * raytilt) + rayadd;

    sf::CircleShape circle(10);
    circle.setOrigin(10, 10);
    circle.setPosition(crossxpos,crossypos);
    _window->draw(circle);
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);

  Chara chara;
  Rays rays(2, 64);
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
    checkConflictAndDraw(&window,rays.getRays(), walls.getWalls());

    window.display();
  }
}
