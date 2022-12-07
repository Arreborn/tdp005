#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{5.0},
      type{'P'}, isJumping{true} {
}

sf::Vector2f verticalPosition(sf::Vector2f &acceleration, bool &isJumping) {
  if (isJumping && acceleration.y < 10){
    acceleration.y += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
      if (!isJumping){
        isJumping = true;
        acceleration.y = -10;
      }
  }
  return acceleration;
}

sf::Vector2f horizontalPosition(){
  sf::Vector2f position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    position.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    position.x += 1;
  }
  return position;
}

void pixelPerfect(shared_ptr<Entity> current, Player* player){
  sf::FloatRect a{current->getBounds()};
  sf::FloatRect p{player->getBounds()};
  int iterations{};
  while (true){
    player->center.y -= 0.001;
    if (p.intersects(a)){ break; }
    ++iterations;
  }
  cout << iterations << endl;
}

bool Player::tick(sf::Time time, World &world) {
  sf::Vector2f vold{center};

  auto vdir{verticalPosition(acceleration, isJumping)};
  //center += vdir * (speed * time.asMicroseconds() / 3000000.0f);
  center += vdir;
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this)) {
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      pixelPerfect(collision, this);
      isJumping = false;
    } else {
      isJumping = true;
    }
  }
  sf::Vector2f hold(center);
  auto hdir(horizontalPosition());
  //center += hdir * (speed * time.asMicroseconds() / 1000000.0f);
  center += hdir * speed;
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