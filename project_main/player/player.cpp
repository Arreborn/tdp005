#include "player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include "../sprites/spriteManager.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

bool canMove{true};

Player::Player(sf::Vector2f center)
    : Entity(center, "sprites/warrior1_new.png"), health{10}, speed{5.0},
      type{'P'}, isJumping{true} {}

sf::Vector2f verticalPosition(sf::Vector2f &acceleration, bool &isJumping, bool const &dashing)
{
  if (dashing)
  {
    return sf::Vector2f{0, 0};
  }
  if (isJumping && acceleration.y < 25)
  {
    if (acceleration.y < 0)
    {
      acceleration.y += 1;
    }
    else if (acceleration.y < 10)
    {
      acceleration.y += 1.5;
    }
    else
    {
      acceleration.y += 1.8;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    if (!isJumping)
    {
      isJumping = true;
      acceleration.y = -10;
    }
  }
  return acceleration;
}

void attack(bool &attacking, sf::Time &attackDuration, char const &attackDirection, sf::Time const &attackDelay)
{
  string slashSprite{"/sprites/swoosh.png"};
  sf::Texture *slSprite = SpriteManager::jjget(slashSprite);
  sf::Sprite slash;
  slash.setTexture(*slSprite);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
  {
    attacking = true;
    attackDuration == sf::seconds(0.2);
  }

  if (attackDirection == 'l' && attacking)
  {
    slash.setTextureRect(sf::IntRect(0, 0, 118, 32));
  }
  else
  {
    slash.setTextureRect(sf::IntRect(0, 0, 118, 32));
  }
}
float dash(bool &dashing, sf::Time &dashDuration, char const &dashDirection, sf::Time const &dashCooldown)
{
  float position{};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !dashing && dashCooldown == sf::seconds(0))
  {
    dashing = true;
    dashDuration = sf::seconds(0.1);
  }

  if (dashDirection == 'l' && dashing)
  {
    position -= 2.5;
  }
  else if (dashDirection == 'r' && dashing)
  {
    position += 2.5;
  }

  return position;
}

sf::Vector2f horizontalPosition(sf::Time const &time, bool &dashing, char &direction, sf::Time &dashDuration, sf::Time &dashCooldown)
{
  sf::Vector2f position{};
  if (dashCooldown == sf::seconds(0))
  {
    position.x += dash(dashing, dashDuration, direction, dashCooldown);
  }

  if (dashing)
  {
    dashDuration -= time;
    if (dashDuration <= sf::seconds(0))
    {
      dashDuration = sf::seconds(0);
      dashing = false;
      dashCooldown = sf::seconds(1.5);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !dashing)
  { // left
    position.x -= 1;
    direction = 'l';
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !dashing)
  { // right
    position.x += 1;
    direction = 'r';
  }
  return position;
}

bool Player::tick(sf::Time time, World &world)
{
  sf::Vector2f vold{center};

  auto vdir{verticalPosition(acceleration, isJumping, dashing)};
  center += vdir;
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this))
  { // vertical collision
    if (dynamic_cast<Block *>(collision.get()))
    {
      center = vold;
      if (collision->center.y > center.y)
      {
        center -= sf::Vector2f{0, (center.y - collision.get()->center.y + 15) - float{0.5}};
        acceleration.y = 2;
        isJumping = false;
      }
      else
      {
        acceleration.y = 0;
      }
      break;
    }
    else
    {
      isJumping = true;
    }
  }
  sf::Vector2f hold(center);
  auto hdir(horizontalPosition(time, dashing, direction, dashDuration, dashCooldown));
  center += hdir * speed;
  sprite.setPosition(center);

  for (auto &collision : world.collidesWith(*this))
  { // horiontal collision
    if (dynamic_cast<Block *>(collision.get()))
    {
      center = hold;
      sprite.setPosition(hold);
    }
    // code for enemy collision here?
  }

  if (center.y != vold.y)
  {
    isJumping = true;
  }

  if (dashCooldown >= sf::seconds(0))
  {
    dashCooldown -= time;
    if (dashCooldown <= sf::seconds(0))
    {
      dashCooldown = sf::seconds(0);
    }
  }

  if (direction == 'l')
  {
    attack(attacking, attackDuration, direction, attackDelay);
    sprite.scale(-1.0f, 1.0f);
  }
  else
  {
    sprite.scale(1.f, 1.f);
  }

  return true;
}

void Player::render(sf::RenderWindow &drawTo)
{

  Entity::render(drawTo);
}
