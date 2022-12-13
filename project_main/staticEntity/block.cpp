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

void Block::render(sf::RenderWindow &drawTo) { Entity::render(drawTo); }

void Block::takeDamage(float) { cout << "Block" << endl; }