#include "entity.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Vector2.hpp>

TexturedEntity::TexturedEntity(sf::Vector2f center, const string &sprite)
    : Entity(center, 0.0f)
{

    sf::Texture *t = SpriteManager::get(sprite);
    auto size = t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2.0, size.y / 2.0);
    radius = max(size.x, size.y) / 2.0f;
}

void TexturedEntity::render(sf::RenderWindow &window)
{
    shape.setPosition(center);
    //radius = max(size.x, size.y) / 2.0f;
}

bool Entity::tick(sf::Time, World&){
  return true;
}

void Entity::render(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::RectangleShape *TexturedEntity::getBorder()
{
    return &shape;
}