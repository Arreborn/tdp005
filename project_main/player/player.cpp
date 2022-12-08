#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{5.0},
      type{'P'}, isJumping{true} {}

sf::Vector2f verticalPosition(sf::Vector2f &acceleration, bool &isJumping) {
  if (isJumping && acceleration.y < 30){
    if (acceleration.y < 0){
      acceleration.y += 1;
    } else if (acceleration.y < 10){
      acceleration.y += 1.5;
    } else {
      acceleration.y += 1.8;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W ) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { 
      if (!isJumping){
        isJumping = true;
        acceleration.y = -10;
      }
  }
  return acceleration;
}

sf::Vector2f horizontalPosition(){
  sf::Vector2f position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // left
    position.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // right
    position.x += 1;
  }
  return position;
}

bool Player::tick(sf::Time, World &world) {
  sf::Vector2f vold{center};

  auto vdir{verticalPosition(acceleration, isJumping)};
  center += vdir;
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      if (collision->center.y > center.y){
        center -= sf::Vector2f{0, (center.y - collision.get()->center.y + 15) - float{0.5}};
        acceleration.y = 2;
        isJumping = false;
      } else {
        acceleration.y = 0;
      }
    } else {
      isJumping = true;
    }
  }
  sf::Vector2f hold(center);
  auto hdir(horizontalPosition());
  center += hdir * speed;
  sprite.setPosition(center);

    for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }
  
  if (center.y != vold.y){
    isJumping = true;
  }
  return true;
}

void Player::render(sf::RenderWindow &drawTo) {

  Entity::render(drawTo);
}