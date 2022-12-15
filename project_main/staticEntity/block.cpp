#include "block.h"
#include "../entity/entity.h"
#include "../world.h"

Block::Block(sf::Vector2f center, const sf::IntRect &tile)
    : Entity(center, "sprites/Tileset.png", 'B') {

  sprite.setTextureRect(tile);
  sprite.setOrigin(0, 0);
};

// mandatory override
bool Block::tick(sf::Time, World &) { return true; }

// not used for this object
void Block::takeDamage(float) {}