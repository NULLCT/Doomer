#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Walls {
private:
  vector<sf::VertexArray> wall;

public:
  Walls() : wall(2,sf::VertexArray(sf::LineStrip,2)){
    wall[0][0].position = sf::Vector2f(100, 100);
    wall[0][1].position = sf::Vector2f(200, 200);

    wall[1][0].position = sf::Vector2f(200, 200);
    wall[1][1].position = sf::Vector2f(100, 300);
  }
  
  void update(sf::RenderWindow* _window) {
    for (auto& i : wall) {
      _window->draw(i);
    }
  }

  vector<sf::VertexArray> *getWalls() {
    return &wall;
  }
};
