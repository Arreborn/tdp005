#include "block.h"
#include "../world.h"
#include "../entity/entity.h"

Block::Block(sf::Vector2f center)
  : Entity(center, "sprites/Grass.png") {
    sprite.setOrigin(0, 0);
  };

// mandatory override
bool Block::tick(sf::Time, World &){
  return true;
}

void Block::render(sf::RenderWindow &drawTo){
  Entity::render(drawTo);
}