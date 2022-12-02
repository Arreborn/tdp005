#include "player.h"
#include "../world.h"
#include "../components/component.h"
#include <SFML/System/Vector2.hpp>

Player::Player(sf::Vector2f center) 
    : BaseClass(center, "sprites/warrior1.png"), health{10}, speed{300.0}, type{'p'} {}

sf::Vector2f find_position() {
    sf::Vector2f position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // this must handle jumps
        position.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        position.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x += 1;

    float len = sqrt(pow(position.x, 2) + pow(position.y, 2)); // why don't brackets work
    if (len > 0.0f)
        return position * (1.0f / len);
    else
        return position;
}

bool Player::tick(sf::Time time, World &world) {
    auto dir{find_position()};
    center += dir * (speed * time.asMicroseconds() / 1000000.0f);

    return true;
}

void Player::render(sf::RenderWindow &drawTo) {
    TexturedEntity::render(drawTo);
}