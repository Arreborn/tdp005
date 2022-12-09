#include "world.h"
#include "player/player.h"
#include <SFML/System/Vector2.hpp>

void World::tick(sf::Time time) {

  for (size_t i{}; i < objects.size(); ++i) {
    if (!objects[i]->tick(time, *this)) {
        objects.erase(objects.begin() + i);
        --i;
    }
  }
}

void World::render(sf::RenderWindow &drawTo) {
  for (auto &x : objects){
    x->render(drawTo);
  }
}

void World::add(shared_ptr<Entity> object) {
  if (dynamic_cast<Player *>(object.get())){
    cout << "Player found!" << endl;
    playerCharacter = object;
  }
  objects.push_back(object);
}

static bool collides(Entity &a, Entity &b) {
  auto aBounds{a.getBorder()->getGlobalBounds()};
  auto bBounds{b.getBorder()->getGlobalBounds()};
  	return (aBounds.intersects(bBounds));
}

vector<shared_ptr<Entity>> World::collidesWith(Entity &me) const {
  vector<shared_ptr<Entity>> result;

  for (auto &x : objects) {
    if (x.get() == &me){
      continue;
    } else if (collides(*x, me)){
      result.push_back(x);
    }
  }
  return result;
}

const sf::Vector2f World::getCenter(){
  sf::Vector2f center{playerCharacter->getCenter()};
  if (center.x <= 320.0f){
    center.x = 320.0f;
  } else if (center.x >= 960){
    center.x = 960.0f;
  }

  if (center.y >= 600){
    center.y = 600;
  } else if (center.y <= 200){
    center.y = 200;
  }

  return center;  
}