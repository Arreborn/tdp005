#include "hostile.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

Hostile::Hostile(sf::Vector2f center)
    : Entity(center, "sprites/mushy_test.png", 'h'), health{100}, speed(5.0) {
  sprite.setOrigin(0, 0);
}

bool Hostile::tick(sf::Time time, World &world) {

  if (blinkDuration <= sf::seconds(0)) {
    sprite.setColor(sf::Color::White);
    blinkDuration = sf::seconds(0);
  } else {
    blinkDuration -= time;
  }

  sf::Vector2f playerPos{world.playerCharacter->getCenter()};
  // cout << "Player: " << playerPos.y << " | Hostile: " << center.y << endl;
  if (playerPos.y == center.y + 1.5f) {
    if (playerPos.x < center.x) {
      direction = 'l';
      center.x -= 0.9f;
    } else {
      direction = 'r';
      center.x += 0.9f;
    }
  } else {
    // random movement
  }

  // collision detection for horizontal movement
  sf::Vector2f hold{center};
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
