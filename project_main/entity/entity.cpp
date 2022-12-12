#include "entity.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Vector2.hpp>

Entity::Entity(sf::Vector2f center, const string &renderSprite, char const type)
    : center(center), type{type} {

    sf::Texture *t = SpriteManager::get(renderSprite);
    auto size = t->getSize();
    // sprite.setSize(sf::Vector2f(size.x, size.y));
    sprite.setTexture(*t);
    sprite.setOrigin(size.x / 2.0, size.y / 2.0);
    radius = max(size.x, size.y) / 2.0f;
    direction = 'r';
}

void Entity::render(sf::RenderWindow &window){
    sprite.setPosition(center);
    window.draw(sprite);
}

sf::Sprite *Entity::getBorder(){
    return &sprite;
}

sf::FloatRect Entity::getBounds(){
    return sprite.getGlobalBounds();
}

sf::Vector2f const Entity::getCenter(){
  return center;
}

bool Entity::isAlive(){
    return true;
}

char Entity::getType(){
    return type;
}

void Entity::takeDamage(float){};

char Entity::getDirection(){
    return direction;
}