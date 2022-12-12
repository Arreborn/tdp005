#pragma once
#include "../entity/entity.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

/**
 * @brief This class defines and handles the player character.
 *
 */
class Player : public Entity, public std::enable_shared_from_this<Entity>
{
public:
  /**
   * @brief Construct a new Player object.
   *
   * @param center
   */
  Player(sf::Vector2f center);

  /**
   * @brief Updates player position.
   *
   * @param time
   * @param world
   * @return true
   * @return false
   */
  bool tick(sf::Time time, World &world) override;

  /**
   * @brief Draws the player in the game world.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo) override;

  sf::Vector2f verticalPosition();

  float dash();

  sf::Vector2f horizontalPosition(sf::Time const &time);

  /**
   * @brief Checks if players movement is about to escape the playing field.
   *
   * @return true
   * @return false
   */
  bool borderCheck();

  bool isAlive() override;

  void attack(World &world);

  void takeDamage(float damage) override;

  shared_ptr<Entity> ptrGet();

protected:
  /**
   * @brief Player health. Always decreases by one when hit.
   *
   */
  int health{};

  bool isHit{};

  /**
   * @brief Player speed. Used to manipulate movement speed. 5.0 by default.
   *
   */
  float speed{};

  /**
   * @brief This bool activates when the player is in the air, to accelerate
   * the gravitational pull.
   *
   */
  bool isJumping{};

  /**
   * @brief This bool signifies whether or not the player is currently dashing.
   *
   */
  bool dashing{};

  /**
   * @brief This bool checks if the player has collided with an enemy, and will
   * be thrown.
   *
   */
  bool thrown{};

  /**
   * @brief This char manages the direction the player is facing. Value: left =
   * 'l', right = 'r'.
   *
   */
  // char direction{};

  /**
   * @brief This vector is used to simulate gravitational pull.
   *
   */
  sf::Vector2f acceleration{sf::Vector2f(0, 0)};

  /**
   * @brief The duration the player has been dashing. When at 0, the dash ends.
   *
   */
  sf::Time dashDuration{};

  /**
   * @brief During the cooldown, the player cannot dash again.
   *
   */
  sf::Time dashCooldown{};

  sf::Time attackCooldown{};

  sf::Time iFrame{};
};