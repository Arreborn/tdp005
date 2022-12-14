#include "rangedAttack.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

RangedAttack::RangedAttack(sf::Vector2f center, float damage,
                           shared_ptr<Entity> attacker)
    : Attack{center, damage, attacker}, damage{damage} {
  sf::Texture *t = SpriteManager::get("sprites/Arrow.png");
  auto size = t->getSize();
  sprite.setTexture(*t);
  sprite.setOrigin(0, size.y / 2.0);
  sprite.setTextureRect(sf::IntRect(0, 0, 16, 8));
  type = 'a';

  thisAttacker = attacker.get();

  // center = thisAttacker->center;
  if (thisAttacker->getDirection() == 'l') {
    attackDirection = 'l';
    center -= sf::Vector2f(64, 0);
    sprite.setScale(-0.75, 0.75);
  } else if (thisAttacker->getDirection() == 'r') {
    attackDirection = 'r';
    center += sf::Vector2f(64, 0);
    sprite.setScale(0.75, 0.75);
  }
}

bool RangedAttack::tick(sf::Time, World &world) {

  if (attackDirection == 'l') {
    center.x -= 6;
  } else if (attackDirection == 'r') {
    center.x += 6;
  }
  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Entity *>(collision.get())->getType() !=
        thisAttacker->getType()) {
      if (!dynamic_cast<Block *>(collision.get())) {
        collision->takeDamage(damage);
      }
      return false;
    }
  }

  if (tickCount == 7) {
    tickCount = 0;
    switch (animation) {
    case 1:
      sprite.setTextureRect(sf::IntRect(0, 0, 28, 16));
      attackDuration = sf::seconds(1);
      break;
    case 2:
      sprite.setTextureRect(sf::IntRect(32, 0, 28, 16));
      attackDuration = sf::seconds(1);
      break;
    case 3:
      sprite.setTextureRect(sf::IntRect(64, 0, 28, 16));
      attackDuration = sf::seconds(1);
      break;
    case 4:
      sprite.setTextureRect(sf::IntRect(96, 0, 28, 16));
      attackDuration = sf::seconds(1);
      break;
    }

    ++animation;
    if (animation == 5) {
      animation = 1;
    }
  } else {
    ++tickCount;
  }

  if (center.x == 0 || center.x == 1280) {
    return false;
  } else {
    return true;
  }
}

void RangedAttack::render(sf::RenderWindow &render) { Entity::render(render); }

void RangedAttack::takeDamage(float) { cout << "Collided with itself" << endl; }