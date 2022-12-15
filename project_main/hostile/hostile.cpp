#include "hostile.h"
#include "../attack/attack.h"
#include "../attack/rangedAttack.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <tuple>

Hostile::Hostile(sf::Vector2f center)
    : Entity(center, "sprites/Enemie_sheet.png", 'h'), health{100}, speed(5.0) {
  sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
  sprite.setOrigin(0, 0);
}

void Hostile::horizontalPosition(const sf::Time &time, World &world) {
  if (chargeUp != sf::seconds(0.0f)) {
    return;
  }
  float xOffset{};
  float yOffset{getBounds().top + 16 + 1};
  if (direction == 'l') {
    xOffset = getBounds().left - 1;
  } else if (direction == 'r') {
    xOffset = getBounds().left + getBounds().width + 1;
  }

  sf::Vector2f playerPos{world.playerCharacter->getCenter()};
  if (playerPos.y == center.y + 1.5) {
    if (playerPos.x < center.x) {
      direction = 'l';
      if (world.detectEdge(xOffset, yOffset)) {
        center.x -= 1;
      }
    } else {
      direction = 'r';
      if (world.detectEdge(xOffset, yOffset)) {
        center.x += 1;
      }
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

// not used for this object
void Hostile::verticalPosition(sf::Time const &, World &) {}

// this tick is used for all hostiles
bool Hostile::tick(sf::Time time, World &world) {

  // toggles damage indicator when the enemy has been hit
  if (blinkDuration <= sf::seconds(0)) {
    sprite.setColor(sf::Color::White);
    blinkDuration = sf::seconds(0);
  } else {
    blinkDuration -= time;
  }

  // runs the code for attacking for this specific hostile
  attack(world);

  if (chargeUp > sf::seconds(0)) {
    chargeUp -= time;
  }

  // manages attack cooldown
  if (attackCooldown <= sf::seconds(0.0f)) {
    attackCooldown = sf::seconds(0.0f);
  } else {
    attackCooldown -= time;
  }

  // manages vertical collision when applicable
  verticalPosition(time, world);
  sf::Vector2f hold{center};
  // collision detection for horizontal movement
  horizontalPosition(time, world);
  for (shared_ptr<Entity> &collision :
       world.collidesWith(*this)) { // horiontal collision
    if (dynamic_cast<Block *>(collision.get()) ||
        dynamic_cast<Player *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }

  // fixes sprite direction
  if (direction == 'l') {
    sprite.setScale(-1.0f, 1.0f);
  } else {
    sprite.setScale(1.f, 1.f);
  }

  // removes dead enemues
  if (!isAlive()) {
    world.removeEnemy();
    return false;
  } else {
    return true;
  }
};

// this is a standard melee attack
void Hostile::attack(World &world) {

  // finds coordinates in front of the hostile
  float xCoord{};
  if (direction == 'l') {
    xCoord = getBounds().left - 20;
  } else if (direction == 'r') {
    xCoord = getBounds().left + getBounds().width + 20;
  }

  // if the player is close to the hostile, it will attack
  if (world.playerCharacter->getBounds().contains(xCoord, center.y + 12) &&
      attackCooldown == sf::seconds(0.0f)) {
    if (chargeUp == sf::seconds(0.0)) {
      chargeUp = sf::seconds(0.4);
    }
  }

  if (chargeUp < sf::seconds(0.0f)) {
    chargeUp = sf::seconds(0);
    sprite.setColor(sf::Color::White);
    world.add(std::make_shared<Attack>(center, 1, ptrGet()));
    attackCooldown = sf::seconds(2.0f);
  } else if (chargeUp != sf::seconds(0.0f)) {
    sprite.setColor(sf::Color(176, 224, 230));
  }
}

bool Hostile::isAlive() {
  if (health <= 0) {
    return false;
  } else {
    return true;
  }
}

void Hostile::takeDamage(float damage) {
  if (isAlive()) {
    health -= damage;
    sprite.setColor(sf::Color::Red);
    blinkDuration = sf::seconds(0.4f);
  }
}
