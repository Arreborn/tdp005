#include "attack.h"
#include <SFML/System/Vector2.hpp>

Attack::Attack(sf::Vector2f center, float damage, shared_ptr<Entity> attacker)
    : Entity{center, "sprites/swoosh.png", 'a'}, damage{damage}{
  thisAttacker = attacker.get();
  sprite.setTextureRect(sf::IntRect(
      0, 0, 30, 30)); // edit attackDuration to adjust duration of attacks
}

bool Attack::tick(sf::Time time, World &world) {
  center = thisAttacker->center;
  if (thisAttacker->getDirection() == 'l'){
    center.x -= 65;
    sprite.setScale(-1, 1);
  } else if (thisAttacker->getDirection() == 'r'){
    center.x += 65;
    sprite.setScale(1, 1);
  }
  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Entity *>(collision.get())->getType() !=
            thisAttacker->getType() &&
        !(dynamic_cast<Block *>(collision.get()))) {
      collision->takeDamage(damage);
    }
  }
  float duration{30.0f};
  if (attackDuration.asMilliseconds() <= duration) {
    sprite.setTextureRect(sf::IntRect(28, 0, 30, 32));
  } else if (attackDuration.asMilliseconds() <= duration * 2) {
    sprite.setTextureRect(sf::IntRect(56, 0, 30, 32));
  } else if (attackDuration.asMilliseconds() <= duration * 3) {
    sprite.setTextureRect(sf::IntRect(84, 0, 30, 32));
  }

  attackDuration += time;

  if (attackDuration.asMilliseconds() >= duration * 4) {
    return false;
  } else {
    return true;
  }
}

void Attack::render(sf::RenderWindow &render) { Entity::render(render); }