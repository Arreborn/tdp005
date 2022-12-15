#include "archer.h"
#include "../attack/rangedAttack.h"
#include "../staticEntity/block.h"
#include "../world.h"

Archer::Archer(sf::Vector2f center) : Hostile(center) {
  type = 'h';
  health = 60;
  speed = 6.0;
  sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
  sprite.setOrigin(0, 0);
}

void Archer::horizontalPosition(sf::Time const &time, World &world) {
  // detects an edge to not walk off it
  float xOffset{};
  float yOffset{getBounds().top + 16 + 1};
  if (direction == 'l') {
    xOffset = getBounds().left - 1;
  } else if (direction == 'r') {
    xOffset = getBounds().left + getBounds().width + 1;
  }

  // defines movement
  // will walk towards player if they're on the same y coordinate
  // will stop if 200 pixels away from the player
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};
  if (playerPos.y == center.y + 1.5) {
    if (playerPos.x < center.x) {
      direction = 'l';
    } else if (playerPos.x > center.x) {
      direction = 'r';
    }
    if (playerPos.x < center.x - 200) {
      if (world.detectEdge(xOffset, yOffset)) {
        center.x -= 1;
      }
    } else if (playerPos.x > center.x + 200) {
      if (world.detectEdge(xOffset, yOffset)) {
        center.x += 1;
      }
    }
  } else { // if not on the same coordinate, uses random behaviour
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
      if (world.detectEdge(xOffset, yOffset)) {
        center.x -= 1;
      }

      movementDuration -= time;

    } else if (direction == 'r' && movementDuration > sf::seconds(0)) {
      if (world.detectEdge(xOffset, yOffset)) {
        center.x += 1;
      }
      movementDuration -= time;
    }
  }
}

void Archer::attack(World &world) {
  if (attackCooldown == sf::seconds(0.0f) &&
      (world.playerCharacter->getCenter().x > center.x - 200 ||
       world.playerCharacter->getCenter().x < center.x + 200) &&
      world.playerCharacter->getCenter().y == center.y + 1.5) {

    if (chargeUp == sf::seconds(0.0)) {
      chargeUp = sf::seconds(0.4);
    }
  }

  if (chargeUp < sf::seconds(0.0f)) {
    chargeUp = sf::seconds(0);
    sprite.setColor(sf::Color::White);
    world.add(std::make_shared<RangedAttack>(center, 1, ptrGet()));
    attackCooldown = sf::seconds(2.0f);
  } else if (chargeUp != sf::seconds(0.0f)) {
    sprite.setColor(sf::Color(176, 224, 230));
  }
}
