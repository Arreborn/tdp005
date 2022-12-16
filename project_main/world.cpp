#include "world.h"
#include "level/levelConstructor.h"
#include "level/segmentManager.h"
#include "player/player.h"
#include "staticEntity/block.h"
#include <SFML/Graphics/Rect.hpp>

void World::tick(sf::Time time) {
  for (size_t i{}; i < objects.size(); ++i) {
    if (!objects[i]->tick(time, *this)) {
      objects.erase(objects.begin() + i);
      --i;
    }
  }
  cout << "Current stage: " << currentStage << endl;
  cout << "Competed levels: " << completedLevels << endl;
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
  auto aBounds{a.getBounds()};
  auto bBounds{b.getBounds()};
  return (aBounds.intersects(bBounds));
}

vector<shared_ptr<Entity>> World::collidesWith(Entity &me) {
  vector<shared_ptr<Entity>> result;

  // the vector populated here contains all objects that &me collides with
  for (shared_ptr<Entity> &x : objects) {
    if (x.get() == &me) {
      continue;
    } else if (collides(*x, me)) {
      result.push_back(x);
    }
  }
  return result;
}

bool World::detectEdge(float const x, float const y) {
  sf::Rect<float> checking(x, y, 1, 1);
  for (shared_ptr<Entity> &e : objects) {
    if (e.get()->getType() == 'B') {
      if (e->getBounds().intersects(checking)) {
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

void World::clear() {
  for (size_t i{}; i < objects.size(); ++i) {
    if (!dynamic_cast<Player *>(objects[i].get())) {
      objects.erase(objects.begin() + i);
      --i;
    }
  }
}

bool World::victory() {
  if (completedLevels == 6) {
    return true;
  } else {
    return false;
  }
}

void World::addEnemy() { ++enemiesAlive; }

void World::removeEnemy() { --enemiesAlive; }

bool World::levelCleared() {
  if (enemiesAlive == 0) {
    if (currentStage > completedLevels) {
      ++completedLevels;
    }
    return true;
  } else {
    return false;
  }
}

void World::getLevel(bool right, shared_ptr<Player> player) {
  if (loadedSegments.empty()) { // if we have no levels at all yet
    SegmentManager::get(7, loadedSegments);
    LevelConstructor::generateLevel(*this, player, true,
                                    loadedSegments[currentStage]);
  } else {
    if (right) {
      ++currentStage;
    } else { // if we have levels stored
      if (currentStage == 0) {
        return;
      }
      --currentStage;
    }
    if (currentStage > completedLevels) {
      player->heal();
    }
    clear();
    LevelConstructor::generateLevel(*this, player,
                                    (currentStage > completedLevels),
                                    loadedSegments[currentStage]);
  }
}
