#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{100.0},
      type{'P'}, isJumping{true} {
}

sf::Vector2f horizontal_position(sf::Vector2f &acceleration, bool &isJumping) {
  if (isJumping && acceleration.y < 10){
    ++acceleration.y;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // this must handle jumps
      if (!isJumping){
        isJumping = true;
        acceleration.y -= 10;
      }
  }  //position.y -= 1;

  return acceleration;
}

sf::Vector2f vertical_position(){
  sf::Vector2f position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    position.x -= 3.6;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    position.x += 3.6;
  }
  return position;
}

bool Player::tick(sf::Time time, World &world) {
  sf::Vector2f hold{center};
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
  //   Attack::attackMelee();
  // }

  auto hdir{horizontal_position(acceleration, isJumping)};
  center += hdir * (speed * time.asMicroseconds() / 1000000.0f);
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }
  sf::Vector2f vold(center);
  auto vdir(vertical_position());
  center += vdir * (speed * time.asMicroseconds() / 1000000.0f);
  sprite.setPosition(center);

    for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      sprite.setPosition(vold);
    }
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) {
  Entity::render(drawTo);
}