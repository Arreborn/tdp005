#include "entity.h"
#include "../sprites/spriteManager.h"

TexturedEntity::TexturedEntity(sf::Vector2f center, const string &texture) : Entity(center, texture) {
    sf::Texture *t = SpriteManager::get(texture);
    auto size= t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2, size.y / 2);
    radius= max(size.x, size.y) / 2.0f;
}

void TexturedEntity::render(sf::RenderWindow &window) {
    shape.setPosition(center);
    window.draw(shape);
}