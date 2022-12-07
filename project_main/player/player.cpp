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

sf::Vector2f horizontal_position() {
  sf::Vector2f position{0, 1};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // this must handle jumps
    position.y -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    position.y += 1;
  }
    return position;
}

sf::Vector2f vertical_position(){
  sf::Vector2f position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    position.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    position.x += 1;
  }
  return position;
}

bool Player::tick(sf::Time time, World &world) {
  sf::Vector2f hold{center};
  sf::Vector2f vold(center);
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
  //   Attack::attackMelee();
  // }

  auto hdir{horizontal_position()};

  center += hdir * (speed * time.asMicroseconds() / 1000000.0f);
  shape.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = hold;
      shape.setPosition(hold);
    }
  }

  auto vdir(vertical_position());

  center += vdir * (speed * time.asMicroseconds() / 1000000.0f);
  shape.setPosition(center);

    for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      shape.setPosition(vold);
    }
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) {
  Entity::render(drawTo);
}