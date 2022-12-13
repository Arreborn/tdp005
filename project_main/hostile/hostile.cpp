#include "hostile.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics/RenderWindow.hpp>
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

  // movement and behaviour

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
