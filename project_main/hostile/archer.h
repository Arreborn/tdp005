#pragma once
#include "../common.h"
#include "hostile.h"

/**
 * @brief This sub-class is a basic ranged enemy, which has unique behaviour and
 * attacks compared to the main hostile class.
 */
class Archer : public Hostile {
public:
  /**
   * @brief Construct a new Archer object. Only accepts center which designates
   * the objects position.
   *
   * @param center
   */
  Archer(sf::Vector2f center);

  /**
   * @brief Handles the behaviour for horizontal movement.
   *
   * @param time
   * @param world
   */
  void horizontalPosition(sf::Time const &time, World &world) override;

  /**
   * @brief Checks if an attack is appropriate, and creates a ranged attack
   * object if it is.
   *
   * @param world
   */
  void attack(World &world) override;
};