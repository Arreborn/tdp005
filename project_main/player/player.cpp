#include "player.h"
#include "../world.h"
#include "../components/component.h"
#include <SFML/System/Vector2.hpp>

Player::Player(sf::Vector2f center) 
    : BaseClass(center, "sprites/fighter_idle.png"), health{10}, speed{400.0}, type{'P'} {}

sf::Vector2f find_position() {
    sf::Vector2f position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ // this must handle jumps
        position.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position.x -= 1;
        Animation.update(time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position.x += 1;
        Animation.update(time);
    }
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