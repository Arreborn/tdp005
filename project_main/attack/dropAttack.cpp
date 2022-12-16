#include "dropAttack.h"
#include "../sprites/spriteManager.h"

DropAttack::DropAttack(sf::Vector2f center, float const damage,
                       shared_ptr<Entity> attacker)
    : Attack{center, damage, attacker} {
  sf::Texture *t = SpriteManager::get("sprites/dropping.png");
  auto size = t->getSize();
  sprite.setTexture(*t);
  sprite.setOrigin(0, size.y / 2.0);
  sprite.setTextureRect(sf::IntRect(0, 0, 10, 18));
  type = 'a';

  thisAttacker = attacker.get();
}

bool DropAttack::tick(sf::Time, World &world) {
  // drops the attack straight down
  center.y += 2.5;

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
  return true;
}