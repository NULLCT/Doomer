#include <SFML/Graphics.hpp>
#include "chara.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);

  Chara chara;

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

    window.display();
  }
}
