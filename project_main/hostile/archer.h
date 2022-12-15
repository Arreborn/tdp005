#pragma once
#include "../common.h"
#include "hostile.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

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
   * @brief Updates the object. Will return false when the unit has died.
   *
   * @param time
   * @param world
   * @return true
   * @return false
   */
  bool tick(sf::Time time, World &world) override;

  /**
   * @brief Handles the behaviour for vertical movement. Only utilized in
   * flying.h, only here to allow for the same tick to be used for all hostiles.
   *
   */
  void verticalPosition(sf::Time const &time, World &world) override;

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