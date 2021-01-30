#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "chara.hpp"
#include "rays.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);

  std::cout << "a";
 
  Chara chara;
  Rays rays(10,64);
 
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch(event.type){
        case sf::Event::Closed:
          window.close();
          break;
      }
    }
    window.clear();

    chara.update(&window);
    rays.update(&window, chara.getPosition());

    window.display(); 
  }
}
