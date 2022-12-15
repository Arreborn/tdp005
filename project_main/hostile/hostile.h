#pragma once
#include "../common.h"
#include "../entity/entity.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @brief This is a base class for hostiles. From this, sub-classes for more
 * avanced enemies can be added.
 *
 */
class Hostile : public Entity {
public:
  /**
   * @brief Construct a new Hostile entity.Only accepts center which designates
   * the objects position.
   *
   * @param center
   */
  Hostile(sf::Vector2f center);

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
   * @brief Renders the object.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo) override;

  /**
   * @brief Returns whether the hostile is alive or not.
   *
   * @return true
   * @return false
   */
  bool isAlive() override;

  /**
   * @brief Allows the entity to take damage.
   *
   * @param damage
   */
  void takeDamage(float damage) override;

  /**
   * @brief Handles the behaviour for vertical movement. DEPRECATED?
   *
   */
  virtual void verticalPosition(sf::Time const &time, World &world);

  /**
   * @brief Handles the behaviour for horizontal movement.
   *
   * @param time
   * @param world
   */
  virtual void horizontalPosition(sf::Time const &time, World &world);

  /**
   * @brief Checks if an attack is appropriate, and creates a ranged attack
   * object if it is.
   *
   * @param world
   */
  virtual void attack(World &world);

protected:
  /**
   * @brief Stores the health of the hostile.
   *
   */
  int health{};

  /**
   * @brief The units movement speed.
   *
   */
  float speed{};

  /**
   * @brief Stores the acceleration for the hostile, which allows them to
   * be affected by gravity.
   *
   */
  sf::Vector2f acceleration{0, 2};

  /**
   * @brief When taking damage, the hostile will turn red momentarily. This
   * variable stores the current color.
   *
   */
  sf::Time blinkDuration{};
  sf::Time attackCooldown{};

  sf::Time movementDuration{};
};