#include "entity.h"
#include "../sprites/spriteManager.h"

Entity::Entity(sf::Vector2f center, const string &renderSprite)
    : center(center) {

    sf::Texture *t = SpriteManager::get(renderSprite);
    auto size = t->getSize();
    // sprite.setSize(sf::Vector2f(size.x, size.y));
    sprite.setTexture(*t);
    sprite.setOrigin(size.x / 2.0, size.y / 2.0);
    radius = max(size.x, size.y) / 2.0f;
}

void Entity::render(sf::RenderWindow &window){
    sprite.setPosition(center);
    window.draw(sprite);
}

sf::Sprite *Entity::getBorder(){
    return &sprite;
}