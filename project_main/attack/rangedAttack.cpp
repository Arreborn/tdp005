#include "rangedAttack.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

RangedAttack::RangedAttack(sf::Vector2f center, float damage,
                           shared_ptr<Entity> attacker)
    : Attack{center, damage, attacker} {
  sf::Texture *t = SpriteManager::get("sprites/Arrow.png");
  auto size = t->getSize();
  sprite.setTexture(*t);
  sprite.setOrigin(0, size.y / 2.0);
  sprite.setTextureRect(sf::IntRect(0, 0, 16, 8));
  type = 'a';

  thisAttacker = attacker.get();
  attackDirection = thisAttacker->getDirection();
  // sets the position of the spite depending on the direction the character
  // using it
  if (attackDirection == 'l') {
    center -= sf::Vector2f(64, 0);
    sprite.setScale(-0.75, 0.75);
  } else if (attackDirection == 'r') {
    center += sf::Vector2f(64, 0);
    sprite.setScale(0.75, 0.75);
  }
}

bool RangedAttack::tick(sf::Time, World &world) {

  // travels in the correct direction
  if (attackDirection == 'l') {
    center.x -= 6;
  } else if (attackDirection == 'r') {
    center.x += 6;
  }

  // checks for collision and damages anything that isn't a block and the same
  // type as this, asks to be removed after collision
  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Entity *>(collision.get())->getType() !=
            thisAttacker->getType() &&
        !dynamic_cast<Attack *>(collision.get())) {
      if (!dynamic_cast<Block *>(collision.get())) {
        collision->takeDamage(damage);
      }
      return false;
    }
  }

  // handles animations after 7 ticks
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
  } else { // ups the tickcount after every tick that doesn't update the
           // animation
    ++tickCount;
  }

  // removes the object if it is out of bounds
  if (center.x == 0 || center.x == 1280) {
    return false;
  } else {
    return true;
  }
}

// not used for this object
void RangedAttack::takeDamage(float) {}