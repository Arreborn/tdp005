#include "hostile.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <tuple>

Hostile::Hostile(sf::Vector2f center)
    : Entity(center, "sprites/mushy_test.png", 'h'), health{100}, speed(5.0) {
  sprite.setOrigin(0, 0);
}

void Hostile::horizontalPosition(const sf::Time &time, World &world) {
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

void Hostile::verticaPositon() { center.y += 4; }

bool Hostile::tick(sf::Time time, World &world) {

  /*   sf::Vector2f vold{center};
    verticaPositon();
    sprite.setPosition(center);
    for (shared_ptr<Entity> &collision : world.collidesWith(*this)) {
      if (dynamic_cast<Block *>(collision.get())) {
        center = vold;
        center -= sf::Vector2f{0, (center.y - collision.get()->center.y + 15) +
                                      float{1.2}};
      }
    } */

  // toggles damage indicator
  if (blinkDuration <= sf::seconds(0)) {
    sprite.setColor(sf::Color::White);
    blinkDuration = sf::seconds(0);
  } else {
    blinkDuration -= time;
  }

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

  if (direction == 'l') {
    sprite.setScale(-1.0f, 1.0f);
  } else {
    sprite.setScale(1.f, 1.f);
  }

  if (!isAlive()) {
    world.removeEnemy();
    return false;
  }

  return true;
};

void Hostile::render(sf::RenderWindow &drawTo) { Entity::render(drawTo); }

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
    cout << health << endl;
  }
}
