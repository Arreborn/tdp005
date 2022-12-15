#include "flying.h"
#include "../attack/dropAttack.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Flying::Flying(sf::Vector2f center) : Hostile(center) {
  type = 'h';
  health = 50;
  speed = 7.0;
  sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
  sprite.setOrigin(0, 0);
  canAttack = false;
  attackCooldown = sf::seconds(0.0f);
}

void Flying::verticalPosition(sf::Time const &time, World &world) {
  sf::Vector2f vold{center};
  // the flying enemy will have some variance in its max position
  bool yMax{false};
  float randomHeight{
      1.0f + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))};
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};

  // checks if max coordinate (with variance) has been reached
  if (playerPos.y >= center.y + (60 + (10 * randomHeight))) {
    yMax = true;
  }

  // gives some ranomness to the movement
  int random{rand() % 100 + 1};
  if (random >= 99) {
    movementDuration += sf::seconds(0.2);
  } else if (random <= 2) {
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

  // vertical collision detection
  for (shared_ptr<Entity> &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      center.y -= 1;
    }
  }
}

void Flying::horizontalPosition(sf::Time const &time, World &world) {
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};

  if (attackCooldown == sf::seconds(0.0f)) {
    if (playerPos.x < center.x) {
      direction = 'l';
      // if adding or removing 2 in these cases, the movement breaks
      // why that happens is a great question, one we do not have time to ponder
      center.x -= 1;
      center.x -= 1;
    } else if (playerPos.x > center.x) {
      direction = 'r';
      center.x += 1;
      center.x += 1;
    } else {
      canAttack = true;
    }
    // if the sprite starts glitchin out due to being awfully close to its
    // target, this fixes the positioning
    if ((playerPos.x > center.x && playerPos.x - center.x < 2) ||
        (center.x > playerPos.x && center.x - playerPos.x < 2)) {
      center.x = playerPos.x;
    }
  } else { // random movement
    canAttack = false;
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
  }
}
