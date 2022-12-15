#include "flying.h"
#include "../attack/dropAttack.h"
#include "../staticEntity/block.h"
#include "../world.h"

Flying::Flying(sf::Vector2f center) : Hostile(center) {
  type = 'h';
  health = 50;
  speed = 7.0;
  sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
  sprite.setOrigin(0, 0);
}

void Flying::verticalPosition(sf::Time const &time, World &world) {
  bool yMax{};
  float randomHeight{
      1.0f + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))};
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};
  // sf::Vector2f vold{center};

  if (playerPos.y >= center.y + (85 + (10 * randomHeight))) {
    yMax = true;
  } else if (playerPos.y < center.y) {
    yMax = false;
  }

  for (shared_ptr<Entity> &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      if (collision->getBounds().contains(collision->center.x,
                                          getBounds().top - 16)) {
        yMax = false;
      } else if (collision->getBounds().contains(collision->center.x,
                                                 getBounds().top - 16 -
                                                     getBounds().height)) {
        yMax = true;
      }
    }
  }

  if (attackCooldown == sf::seconds(0.0f) &&
      (playerPos.x > center.x - 150 || playerPos.x < center.x + 150)) {
    if (playerPos.x > center.x) {
      center.x += 1;
    } else if (playerPos.x < center.x) {
      center.x -= 1;
    }
  }

  int random{rand() % 100 + 1};
  if (random == 100) {
    movementDuration += sf::seconds(0.2);
  } else if (random == 1) {
    movementDuration += sf::seconds(0.2);
  }

  if (movementDuration < sf::seconds(0)) {
    movementDuration = sf::seconds(0);
  } else if (!yMax && movementDuration > sf::seconds(0)) {
    center.y -= 1;
    movementDuration -= time;
  } else if (yMax || movementDuration > sf::seconds(0)) {
    center.y += 1;
    movementDuration -= time;
  }
}

void Flying::horizontalPosition(sf::Time const &time, World &world) {
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};

  if (attackCooldown == sf::seconds(0.0f)) {
    if (playerPos.x < center.x) {
      direction = 'l';
      center.x -= 1;
    } else if (playerPos.x > center.x) {
      direction = 'r';
      center.x += 1;
    } else {
      canAttack = true;
    }
  } else {
    int random{rand() % 100 + 1};
    if (random == 100) {
      direction = 'l';
      movementDuration += sf::seconds(0.2);
    } else if (random == 1) {
      direction = 'r';
      movementDuration += sf::seconds(0.2);
    }

    if (movementDuration < sf::seconds(0)) {
      movementDuration = sf::seconds(0);
    } else if (direction == 'l' && movementDuration > sf::seconds(0)) {
      center.x -= 1;
      movementDuration -= time;
    } else if (direction == 'r' && movementDuration > sf::seconds(0)) {
      center.x += 1;
      movementDuration -= time;
    }
  }
}

void Flying::attack(World &world) {
  if (attackCooldown == sf::seconds(0.0f) && canAttack) {
    world.add(std::make_shared<DropAttack>(center, 1, ptrGet()));
    attackCooldown = sf::seconds(5.0f);
    canAttack = false;
  }
}
