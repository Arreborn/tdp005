#include "player.h"
#include "../world.h"
#include "../staticEntity/block.h"
#include <SFML/System/Vector2.hpp>

Player::Player(sf::Vector2f center) 
    : Entity(center, "sprites/warrior1.png"), health{10}, speed{400.0}, type{'P'} {
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(2);
    }

sf::Vector2f findPosition() {
    sf::Vector2f position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ // this must handle jumps
        position.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position.x += 1;
    }
    float len = sqrt(pow(position.x, 2) + pow(position.y, 2)); // why don't brackets work
    if (len > 0.0f)
        return position * (1.0f / len);
    else
        return position;
}

bool Player::tick(sf::Time time, World &world) {
    
    for (auto &collision : world.collidesWith(*this)){
        if (dynamic_cast<Block *>(collision.get())){
            // här ser vi någon typ av kollision
        }
    }
    
    auto dir{findPosition()};
    center += dir * (speed * time.asMicroseconds() / 1000000.0f);
    return true;
}

void Player::render(sf::RenderWindow &drawTo) {
    Entity::render(drawTo);
}