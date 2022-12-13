#include "player.h"
#include "../attack/attack.h"
#include "../hostile/hostile.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <memory>

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png", 'p'), health{10}, speed{5.0},
      isJumping{true} {}

sf::Vector2f Player::verticalPosition() {
  if (dashing) {
    return sf::Vector2f{0, 0};
  }
  if (isJumping && acceleration.y < 25) {
    if (acceleration.y < 0) {
      acceleration.y += 1;
    } else if (acceleration.y < 10) {
      acceleration.y += 1.5;
    } else {
      acceleration.y += 1.8;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (!isJumping) {
      isJumping = true;
      acceleration.y = -10;
    }
  }
  return acceleration;
}

void Player::attack(World &world) {

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) &&
      attackCooldown == sf::seconds(0.0f)) {
    world.add(std::make_shared<Attack>(center, 5, ptrGet()));
    attackCooldown = sf::seconds(0.4f);
  }
}

float Player::dash() {
  float position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !dashing &&
      dashCooldown == sf::seconds(0)) {
    dashing = true;
    dashDuration = sf::seconds(0.1);
  }

  if (direction == 'l' && dashing) {
    position -= 2.5;
  } else if (direction == 'r' && dashing) {
    position += 2.5;
  }

  return position;
}

sf::Vector2f Player::horizontalPosition(sf::Time const &time) {
  sf::Vector2f position{};
  if (dashCooldown == sf::seconds(0)) {
    position.x += dash();
  }

  if (thrown) {
    position.x += acceleration.x;
    if (direction == 'l') {
      if (acceleration.x != 0) {
        acceleration.x -= 0.5;
      }
    } else if (direction == 'r') {
      if (acceleration.x != 0) {
        acceleration.x += 0.5;
      }
    }
  }

  if (dashing) {
    dashDuration -= time;
    if (dashDuration <= sf::seconds(0)) {
      dashDuration = sf::seconds(0);
      dashing = false;
      dashCooldown = sf::seconds(1.5);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !dashing &&
      !thrown) { // left
    position.x -= 1;
    direction = 'l';
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !dashing &&
      !thrown) { // right
    position.x += 1;
    direction = 'r';
  }
  return position;
}

// TODO:
// Consider moving the collision with blocks to the base class

bool Player::tick(sf::Time time, World &world) {
  takeDamage(1);
  if (iFrame <= sf::seconds(0)) {
    iFrame = sf::seconds(0);
  } else {
    iFrame -= time;
  }

  // if (iFrame >= sf::seconds(0))
  // {
  //   iFrame -= time;
  //   if (iFrame <= sf::seconds(0))
  //   {
  //     iFrame = sf::seconds(0);
  //   }
  // }

  if (!isAlive()) {

    // Game over screen???
    // Death animation
    return false;
  }
  // coordinates to reset the player to if a collision is triggered
  sf::Vector2f vold{center};

  sf::Vector2f vdir{verticalPosition()};
  center += vdir;
  sprite.setPosition(center);

  // checks with all entities currently colliding with the player
  for (shared_ptr<Entity> &collision :
       world.collidesWith(*this)) { // vertical collision

    // collision with block
    if (dynamic_cast<Block *>(collision.get())) {
      center = vold;
      // this case manages pixel perfect contact with the ground
      if (collision->center.y > center.y) {
        center -= sf::Vector2f{0, (center.y - collision.get()->center.y + 15) -
                                      float{0.5}};
        acceleration.y = 2; // standard gravitational pull
        isJumping = false;
        thrown = false;
      } else { // unclear when we enter this
        acceleration.y = 0;
      }
      // break the loop if we collide with a block
      break;
    } else if (dynamic_cast<Hostile *>(collision.get())) {
      // vertical collision with an enemy will get the player thrown back
      center = vold;
      // gives some lift when being thrown
      acceleration.y = -6;
      // ensures that the player is not considered landing
      isJumping = false;
      // is used to trigger another path in vertical movement
      thrown = true;
      // these variables control the distance a player hets thrown
      if (direction == 'l') {
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

  for (shared_ptr<Entity> &collision :
       world.collidesWith(*this)) { // horiontal collision
    if (dynamic_cast<Block *>(collision.get()) ||
        dynamic_cast<Hostile *>(collision.get())) {
      center = hold;
      sprite.setPosition(hold);
    }
  }

  if (center.x < 0 || center.x > 1280) {
    center = hold;
    sprite.setPosition(hold);
    atBorder = true;
  } else {
    atBorder = false;
  }

  if (center.y != vold.y) {
    isJumping = true;
  }

  if (dashCooldown >= sf::seconds(0)) {
    dashCooldown -= time;
    if (dashCooldown <= sf::seconds(0)) {
      dashCooldown = sf::seconds(0);
    }
  }

  if (direction == 'l') {
    // attack(attacking, attackDuration, direction, attackDelay);
    sprite.setScale(-1.0f, 1.0f);
  } else {
    sprite.setScale(1.f, 1.f);
  }

  attack(world);

  if (attackCooldown <= sf::seconds(0.0f)) {
    attackCooldown = sf::seconds(0.0f);
  } else {
    attackCooldown -= time;
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo) { Entity::render(drawTo); }

bool Player::isAlive() {
  if (health <= 0) {
    return false;
  } else {
    return true;
  }
}

void Player::takeDamage(float damage) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && isAlive() && !isHit &&
      iFrame == sf::seconds(0)) {
    isHit = true;
    iFrame = sf::seconds(2);
    health -= 10;
    // cout << health << endl;
  }
  if (isHit && iFrame == sf::seconds(0)) {
    isHit = false;
  }
}

std::shared_ptr<Entity> Player::ptrGet() { return shared_from_this(); }

void Player::set(int x, int y) {
  center = sf::Vector2f(x, y);
  sprite.setPosition(center);
}

bool Player::hittingBorder() { return atBorder; }

bool Player::damageTaken() { return isHit; }

int Player::getHealth() { return health; }