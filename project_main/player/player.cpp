#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{100.0},
      type{'P'}, isJumping{true} {
}

sf::Vector2f verticalPosition(sf::Vector2f &acceleration, bool &isJumping) {
  if (isJumping && acceleration.y < 10){
    ++acceleration.y;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // this must handle jumps
      if (!isJumping){
        cout << "Jump" << endl;
        isJumping = true;
        acceleration.y -= 10;
      }
  }  //position.y -= 1;

  return acceleration;
}

sf::Vector2f horizontalPosition(){
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
  sf::Vector2f vold{center};
  auto vdir{verticalPosition(acceleration, isJumping)};
  center += vdir * (speed * time.asMicroseconds() / 1000000.0f);
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      sprite.setPosition(vold);
      isJumping = false;
    }
  }
  sf::Vector2f hold(center);
  auto hdir(horizontalPosition());
  center += hdir * (speed * time.asMicroseconds() / 1000000.0f);
  sprite.setPosition(center);

    for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) {
  Entity::render(drawTo);
}