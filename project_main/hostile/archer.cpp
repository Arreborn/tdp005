#include "archer.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include "../attack/attack.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Archer::Archer(sf::Vector2f center) : Hostile(center)
{
    type = 'a';
    health = 60;
    speed = 6.0;
    sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
    sprite.setOrigin(0, 0);
}

bool Archer::tick(sf::Time time, World &world)
{
    sf::Vector2f playerPos{world.playerCharacter->getCenter()};
    if (playerPos.x == center.x + 10)
    {
        world.add(std::make_shared<Attack>(center, 5, ptrGet()));
    }
    return Hostile::tick(time, world);
}

void Archer::render(sf::RenderWindow &drawTo) { Hostile::render(drawTo); }

void Archer::verticalPosition() { cout << "slide to the left" << endl; }

void Archer::horizontalPosition(sf::Time const &time, World &world)
{
    float xOffset{};
    float yOffset{getBounds().top + 16 + 1};
    if (direction == 'l')
    {
        xOffset = getBounds().left - 1;
    }
    else if (direction == 'r')
        if (world.detectEdge(xOffset, yOffset))
        {
            center.x += 1;
        }
    {
        xOffset = getBounds().left + getBounds().width + 1;
    }

    int random{rand() % 100 + 1};
    if (random == 100)
    {
        direction = 'l';
        movementDuration += sf::seconds(0.2);
    }
    else if (random == 1)
    {
        direction = 'r';
        movementDuration += sf::seconds(0.2);
    }

    if (movementDuration < sf::seconds(0))
    {
        movementDuration = sf::seconds(0);
    }
    else if (direction == 'l' && movementDuration > sf::seconds(0))
    {
        if (world.detectEdge(xOffset, yOffset))
        {
            center.x -= 1;
        }
        movementDuration -= time;
    }
    else if (direction == 'r' && movementDuration > sf::seconds(0))
    {
        if (world.detectEdge(xOffset, yOffset))
        {
            center.x += 1;
        }
        movementDuration -= time;
        // Hostile::horizontalPosition(time, world);
    }
}

void Archer::attack()
{
}
