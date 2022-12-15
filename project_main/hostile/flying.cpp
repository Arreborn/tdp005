#include "flying.h"
#include "../attack/rangedAttack.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Flying::Flying(sf::Vector2f center) : Hostile(center) {
  type = 'f';
  health = 50;
  speed = 7.0;
  sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
  sprite.setOrigin(0, 0);
}

bool Flying::tick(sf::Time time, World &world) {
  return Hostile::tick(time, world);
}

void Flying::verticalPosition(sf::Time const &time, World &world) {
  bool yMax{};
  sf::Vector2f playerPos{world.playerCharacter->getCenter()};
  // sf::Vector2f vold{center};

  cout << "Player y: " << playerPos.y << " enemy: " << center.y << endl;

  if (playerPos.y >= center.y + 75) {
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

void Flying::horizontalPosition(sf::Time const &time, World &) {

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

void Flying::attack(World &world) {}
