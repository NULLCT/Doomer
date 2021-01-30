#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "chara.hpp"
#include "rays.hpp"
#include "walls.hpp"

using namespace std;

void checkConflictAndDraw(sf::RenderWindow *_window, vector<sf::Vertex[2]>* rays, vector<sf::Vertex[2]>* walls) {
  for (auto& ray : *rays) {
    //TODO: ditect conflict
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);

  Chara chara;
  Rays rays(10, 64);
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
