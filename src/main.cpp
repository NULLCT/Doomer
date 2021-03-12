#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "chara.hpp"
#include "rays.hpp"
#include "walls.hpp"
#include "checkconflict.hpp"

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);

  Chara chara;
  Rays rays(128,256);
  Walls walls;
  CheckConflict checkconflicter(rays.getRays()->size());

  bool mousetr = false;

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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!mousetr) {
        mousetr = true;
        walls.getWalls()->push_back(sf::VertexArray(sf::LineStrip, 2));
        (walls.getWalls()->end()-1)[0][0].position = sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
        (walls.getWalls()->end()-1)[0][1].position = chara.getPosition();
      }
    }
    else {
      mousetr = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
      walls.getWalls()->clear();
    }

    chara.update(&window);
    rays.update(&window, chara.getPosition());
    walls.update(&window);
    checkconflicter.update(&window,rays.getRays(), walls.getWalls(),chara.getPosition(),rays.getRayLength(),rays.getDirectionBetweenCharaToMouse(&window,chara.getPosition()));

    window.display();
  }
}
