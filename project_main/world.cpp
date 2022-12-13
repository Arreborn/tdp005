#include "world.h"
#include "player/player.h"
#include "staticEntity/block.h"

void World::tick(sf::Time time) {
  for (size_t i{}; i < objects.size(); ++i) {
    if (!objects[i]->tick(time, *this)) {
      objects.erase(objects.begin() + i);
      --i;
    }
  }
}

void World::render(sf::RenderWindow &drawTo) {
  for (auto &x : objects) {
    x->render(drawTo);
  }
}

void World::add(shared_ptr<Entity> object) {
  if (dynamic_cast<Player *>(object.get())) {
    playerCharacter = object;
  }
  objects.push_back(object);
}

static bool collides(Entity &a, Entity &b) {
  auto aBounds{a.getBorder()->getGlobalBounds()};
  auto bBounds{b.getBorder()->getGlobalBounds()};
  return (aBounds.intersects(bBounds));
}

vector<shared_ptr<Entity>> World::collidesWith(Entity &me) {
  vector<shared_ptr<Entity>> result;

  for (shared_ptr<Entity> &x : objects) {
    if (x.get() == &me) {
      continue;
    } else if (collides(*x, me)) {
      result.push_back(x);
    }
  }
  return result;
}

bool World::detectEdge(sf::FloatRect &check) {
  for (shared_ptr<Entity> &x : objects) {
    if (dynamic_cast<Block *>(x.get())) {
      if (x->getBounds().intersects(check)) {
        return true;
      }
    }
  }
  return false;
}

const sf::Vector2f World::getCenter() {
  sf::Vector2f center{playerCharacter->getCenter()};
  center.y -= 70;
  if (center.x <= 320.0f) {
    center.x = 320.0f;
  } else if (center.x >= 960) {
    center.x = 960.0f;
  }

  if (center.y >= 600) {
    center.y = 600;
  } else if (center.y <= 200) {
    center.y = 200;
  }

  return center;
}

bool World::isPlayerAlive() { return playerCharacter->isAlive(); }

void World::clear() {
  for (size_t i{}; i < objects.size(); ++i) {
    if (!dynamic_cast<Player *>(objects[i].get())) {
      objects.erase(objects.begin() + i);
      --i;
    }
  }
}

void World::addEnemy() { ++enemiesAlive; }

void World::removeEnemy() { --enemiesAlive; }

bool World::levelCleared() {
  if (enemiesAlive == 0) {
    return true;
  } else {
    return false;
  }
}