#include "entity.h"
#include "../sprites/spriteManager.h"

TexturedEntity::TexturedEntity(sf::Vector2f center, const string &sprite) 
: Entity(center, 0.0f) {
    
    sf::Texture *t = SpriteManager::get(sprite);
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