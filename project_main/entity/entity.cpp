#include "entity.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Vector2.hpp>

// this interfacce class manages base behaviour for all classes that inherit
// from it

Entity::Entity(sf::Vector2f center, string const &renderSprite, char const type)
    : center(center), type{type} {

  // fetches the correct sprite with the sprite manager
  sf::Texture *t = SpriteManager::get(renderSprite);
  auto size = t->getSize();
  // sprite.setSize(sf::Vector2f(size.x, size.y));
  sprite.setTexture(*t);
  sprite.setOrigin(size.x / 2.0, size.y / 2.0);
  radius = max(size.x, size.y) / 2.0f;
  direction = 'r';
}

// renders the object in the game world, is used for all entities
void Entity::render(sf::RenderWindow &window) {
  sprite.setPosition(center);
  window.draw(sprite);
}

std::shared_ptr<Entity> Entity::ptrGet() { return shared_from_this(); }

sf::FloatRect Entity::getBounds() { return sprite.getGlobalBounds(); }

sf::Vector2f const Entity::getCenter() { return center; }

bool Entity::isAlive() { return true; }

char Entity::getType() { return type; }

char Entity::getDirection() { return direction; }
