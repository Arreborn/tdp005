#include "entity.h"
#include "../sprites/spriteManager.h"

Entity::Entity(sf::Vector2f center, const string &sprite)
    : center(center) {

    sf::Texture *t = SpriteManager::get(sprite);
    auto size = t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2.0, size.y / 2.0);
    radius = max(size.x, size.y) / 2.0f;
}

void Entity::render(sf::RenderWindow &window){
    shape.setPosition(center);
    window.draw(shape);
}

sf::RectangleShape *Entity::getBorder(){
    return &shape;
}