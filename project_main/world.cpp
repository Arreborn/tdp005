#include "world.h"

void World::tick(sf::Time time) {

  for (size_t i{0}; i < objects.size(); ++i) {
    if (!objects[i]->tick(time, *this)) {
        objects.erase(objects.begin() + i);
    }
  }
}

void World::render(sf::RenderWindow &drawTo) {
  for (auto &x : objects){
    x->render(drawTo);
  }
}

void World::add(shared_ptr<Entity> object) {
  objects.push_back(object);
}

/* static bool collides(Entity &a, Entity &b) {
  // collision code here
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
} */