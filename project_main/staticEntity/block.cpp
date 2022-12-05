#include "block.h"
#include "../world.h"
#include "../components/component.h"

Block::Block(sf::Vector2f center)
  : BaseClass(center, "sprites/Grass.png") {};

// mandatory override
bool Block::tick(sf::Time, World &){
  return true;
}

void Block::render(sf::RenderWindow &drawTo){
  TexturedEntity::render(drawTo);
}