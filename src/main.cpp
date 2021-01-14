#include <SFML/Graphics.hpp>
#include <tuple>
#include <utility>
#include <iostream>

using namespace std;

class Vec{ // record begin point and end point
public:
  pair<int,int> begin,end;

  Vec(const pair<int,int> &_begin,const pair<int,int> &_end){
    begin=_begin;
    end=_end;
  }
};

class Ray{
public:
  sf::Vertex line[2];

  Ray() {
    line[0] = sf::Vertex(sf::Vector2f(0,0));
    line[1] = sf::Vertex(sf::Vector2f(0,0));
  }

  void setPos(sf::Vector2f _begin,sf::Vector2f _end){
    line[0] = _begin;
    line[1] = _end;
  }
};

class Chara{ // me
private:
  const int size = 20;
public:
  sf::CircleShape shape;

  Chara() : shape(size){
    shape.setFillColor(sf::Color::White);
    shape.setPosition(0,0);
    shape.setOrigin(size,size);
  }

  void move(int _x,int _y){
    shape.setPosition(shape.getPosition() + sf::Vector2f(_x,_y));
  }
};

bool isConfrict(pair<int,int> a0,pair<int,int> a1,pair<int,int> b0,pair<int,int> b1) {
  if (((a0.first - a1.first) * (b0.second - a0.second) + (a0.second - a1.second) * (a0.first - b0.first)) * ((a0.first - a1.first) * (b1.second - a0.second) + (a0.second - a1.second) * (a0.first - b1.first)) < 0)
    if (((b0.first - b1.first) * (a0.second - b0.second) + (b0.second - b1.second) * (b0.first - a0.first)) * ((b0.first - b1.first) * (a1.second - b0.second) + (b0.second - b1.second) * (b0.first - a1.first)) < 0)
      return true;

  return false;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(2000, 1000), "Doomer");
  window.setFramerateLimit(60);

  Chara chara;

  vector<Vec> walls;
  walls.emplace_back(Vec(make_pair(100,100),make_pair(200,300)));

  vector<Ray> rays;
  rays.emplace_back(Ray());
  rays[0].setPos(sf::Vector2f(0,0),sf::Vector2f(0,100));

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
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        chara.move(0,-10);
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        chara.move(-10,0);
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        chara.move(0,10);
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        chara.move(10,0);
      }

      for(auto &wall:walls){
        sf::Vertex line[] = {
          sf::Vertex(sf::Vector2f(wall.begin.first,wall.begin.second)),
          sf::Vertex(sf::Vector2f(wall.end.first,wall.end.second))
        };
        window.draw(line, 2, sf::Lines);
      }

      window.draw(chara.shape);

      rays[0].setPos(chara.shape.getPosition(),chara.shape.getPosition()+sf::Vector2f(0,-100));
      if(isConfrict(make_pair(rays[0].line[0].position.x,rays[0].line[0].position.y),
                    make_pair(rays[0].line[1].position.x,rays[0].line[1].position.y),
                    walls[0].begin,
                    walls[0].end)){
        rays[0].line[0].color = sf::Color::Red;
        rays[0].line[1].color = sf::Color::Red;
        window.draw(sf::CircleShape(1500,500));
      }
      window.draw(rays[0].line,2,sf::Lines);
      rays[0].line[0].color = sf::Color::White;
      rays[0].line[1].color = sf::Color::White;
    }
    window.display();
  }

  return 0;
}
