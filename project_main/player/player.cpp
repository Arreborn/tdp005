#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{400.0},
      type{'P'} {
  shape.setOutlineColor(sf::Color::Blue);
  shape.setOutlineThickness(0);
}

sf::Vector2f find_position() {
  sf::Vector2f position;
  if (!canMove) {
    return position;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // this must handle jumps
    position.y -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    position.y += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    position.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    position.x += 1;
  }
  float len =
      sqrt(pow(position.x, 2) + pow(position.y, 2)); // why don't brackets work
  if (len > 0.0f)
    return position * (1.0f / len);
  else
    return position;
}

bool Player::tick(sf::Time time, World &world) {
  sf::Vector2f old{center};
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
  //   Attack::attackMelee();
  // }

  auto dir{find_position()};
  center += dir * (speed * time.asMicroseconds() / 1000000.0f);
  shape.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = old;
      shape.setPosition(old);
    }
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) {
  Entity::render(drawTo);
}