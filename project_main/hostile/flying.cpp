#include "flying.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include "../attack/rangedAttack.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Flying::Flying(sf::Vector2f center) : Hostile(center)
{
    type = 'f';
    health = 50;
    speed = 7.0;
    sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
    sprite.setOrigin(0, 0);
}

bool Flying::tick(sf::Time time, World &world) { return Hostile::tick(time, world); }

void Flying::render(sf::RenderWindow &drawTo) { Hostile::render(drawTo); }

void Flying::verticalPosition()
{
}

void Flying::horizontalPosition(sf::Time const &time, World &world)
{
}

void Flying::attack(World &world)
{
}