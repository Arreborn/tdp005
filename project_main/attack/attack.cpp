#include "attack.h"
#include <SFML/System/Vector2.hpp>

Attack::Attack(sf::Vector2f center, float const damage,
               shared_ptr<Entity> attacker)
    : Entity{center, "sprites/swoosh.png", 's'}, damage{damage}
{
  thisAttacker = attacker.get();
  sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
  // edit attackDuration to adjust duration of attacks

  meleeDirection = thisAttacker->getDirection();
}

bool Attack::tick(sf::Time time, World &world)
{
  center = thisAttacker->center;

  // sets position for the sprite depending on direction
  if (meleeDirection == 'l')
  {
    center.x -= 65;
    sprite.setScale(-1, 1);
  }
  else if (meleeDirection == 'r')
  {
    center.x += 65;
    sprite.setScale(1, 1);
  }
  else if (meleeDirection == 'u')
  {
    center.x += 2;
    center.y -= 65;
    sprite.setRotation(-90);
  }

  // checks for collision with anything that isn't a block and doesn't have the
  // same type as thisAttacker
  for (auto &collision : world.collidesWith(*this))
  {
    if (dynamic_cast<Entity *>(collision.get())->getType() !=
            thisAttacker->getType() &&
        !(dynamic_cast<Block *>(collision.get())))
    {
      collision->takeDamage(damage);
    }
  }

  // animates the sprite depending on the duration
  float duration{30.0f};
  if (attackDuration.asMilliseconds() <= duration)
  {
    sprite.setTextureRect(sf::IntRect(28, 0, 30, 32));
  }
  else if (attackDuration.asMilliseconds() <= duration * 2)
  {
    sprite.setTextureRect(sf::IntRect(56, 0, 30, 32));
  }
  else if (attackDuration.asMilliseconds() <= duration * 3)
  {
    sprite.setTextureRect(sf::IntRect(84, 0, 30, 32));
  }

  attackDuration += time;

  // returns false if the animation is finished
  if (attackDuration.asMilliseconds() >= duration * 4)
  {
    return false;
  }
  else
  {
    return true;
  }
}

// Not used for this object
void Attack::takeDamage(float) {}