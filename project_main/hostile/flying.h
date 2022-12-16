#pragma once
#include "../common.h"
#include "hostile.h"

/**
 * @brief This sub-class is a basic flying enemy, which has unique behaviour and
 * attacks compared to the main hostile class.
 *
 */
class Flying : public Hostile {
public:
  /**
   * @brief Construct a new Flying object. Only accepts center which designates
   * the objects position.
   *
   * @param center
   */
  Flying(sf::Vector2f center);

  /**
   * @brief Handles the vertical movement.
   *
   * @param time
   * @param world
   */
  void verticalPosition(sf::Time const &time, World &world) override;

  /**
   * @brief Handles the horizontal movement.
   *
   * @param time
   * @param world
   */
  void horizontalPosition(sf::Time const &time, World &world) override;

  /**
   * @brief Checks if an attack is appropriate, and creates a drop attack
   * object if it is.
   *
   * @param world
   */
  void attack(World &world) override;

private:
  /**
   * @brief This bool is used to allow the enemy to attack when it is placed
   * above the player.
   *
   */
  bool canAttack{false};
};