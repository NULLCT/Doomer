#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Walls {
private:
  vector<sf::Vertex[2]> wall;

public:
  Walls() : wall(2){
    wall[0][0].position = sf::Vector2f(0, 0);
    wall[0][1].position = sf::Vector2f(100, 100);

    wall[1][0].position = sf::Vector2f(100, 100);
    wall[1][1].position = sf::Vector2f(0, 200);
  }
  
  void update(sf::RenderWindow* _window) {
    for (auto& i : wall) {
      _window->draw(i,2,sf::Lines);
    }
  }

  vector<sf::Vertex[2]> *getWalls() {
    return &wall;
  }
};