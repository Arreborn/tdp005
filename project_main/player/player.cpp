#include "player.h"
#include "../staticEntity/block.h"
#include "../hostile/hostile.h"
#include "../world.h"
#include <SFML/System/Vector2.hpp>

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{5.0},
      type{'P'}, isJumping{true} {}

sf::Vector2f Player::verticalPosition() {
  if (dashing){
    return sf::Vector2f{0, 0};
  }
  if (isJumping && acceleration.y < 25){
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

float Player::dash(){
  float position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !dashing && dashCooldown == sf::seconds(0)){
    dashing = true;
    dashDuration = sf::seconds(0.1);
  }

  if (direction == 'l' && dashing){
    position -= 2.5;
  } else if (direction == 'r' && dashing) {
    position += 2.5;
  }

return position;
}

sf::Vector2f Player::horizontalPosition(sf::Time const &time/*, bool &dashing, bool &thrown, char &direction, sf::Time &dashDuration, sf::Time &dashCooldown, sf::Vector2f acceleration*/){
  sf::Vector2f position{};
  if (dashCooldown == sf::seconds(0)){
    position.x += dash();
  }

  if (thrown){
    position.x += acceleration.x;
    if (direction == 'l'){
      if (acceleration.x != 0){
        acceleration.x -= 0.5;
      }
    } else if (direction == 'r'){
        if (acceleration.x != 0){
          acceleration.x += 0.5;
      }
    }
  }

  if (dashing){
    dashDuration -= time;
    if (dashDuration <= sf::seconds(0)){
      dashDuration = sf::seconds(0);
      dashing = false;
      dashCooldown = sf::seconds(1.5);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !dashing && !thrown) { // left
    position.x -= 1;
    direction = 'l';
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !dashing && !thrown) { // right
    position.x += 1;
    direction = 'r';
  }
  return position;
}
// TODO:
// Consider moving the collision with blocks to the base class
bool Player::tick(sf::Time time, World &world) {
  // coordinates to reset the player to if a collision is triggered
  sf::Vector2f vold{center};

  auto vdir{verticalPosition()};
  center += vdir;
  sprite.setPosition(center);

  // checks with all entities currently colliding with the player
  for (auto &collision : world.collidesWith(*this)) { // vertical collision
    
    // collision with block
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      // this case manages pixel perfect contact with the ground
      if (collision->center.y > center.y){
        center -= sf::Vector2f{0, (center.y - collision.get()->center.y + 15) - float{0.5}};
        acceleration.y = 2; // standard gravitational pull
        isJumping = false;
        thrown = false;
      } else { // unclear when we enter this
        acceleration.y = 0;
      }
      // break the loop if we collide with a block
      break;

    } else if (dynamic_cast<Hostile *>(collision.get())){
      // vertical collision with an enemy will get the player thrown back
      center = vold;
      // gives some lift when being thrown
      acceleration.y = -6;
      // ensures that the player is not considered landing
      isJumping = false;
      // is used to trigger another path in vertical movement
      thrown = true;
      // these variables control the distance a player hets thrown
      if (direction == 'l'){
        acceleration.x += 4; // increase to throw further
      } else {
        acceleration.x -= 4; // set to same value as previous case
      }
    } else { // is triggered when the player lands
      isJumping = true;
    }
  }

  sf::Vector2f hold(center);
  auto hdir(horizontalPosition(time));
  center += hdir * speed;
  sprite.setPosition(center);

    for (auto &collision : world.collidesWith(*this)) { // horiontal collision
    if (dynamic_cast<Block *>(collision.get()) || dynamic_cast<Hostile *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }
  
  if (center.y != vold.y){
    isJumping = true;
  }

  if (dashCooldown >= sf::seconds(0)){
    dashCooldown -= time;
    if (dashCooldown <= sf::seconds(0)){
      dashCooldown = sf::seconds(0);
    }
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) {

  Entity::render(drawTo);
}