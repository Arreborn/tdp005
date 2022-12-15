#pragma once
#include "../common.h"
#include "../entity/entity.h"

/**
 * @brief This is a general base class handling the creation of
 * block-objects.
 *
 */
class Block : public Entity {
public:
  /**
   * @brief Construct a new Block object.
   *
   * @param center
   */
  Block(sf::Vector2f center,
        const sf::IntRect &tile); // maybe top left corner for easier drawing?

  /**
   * @brief Handles updates for collision checking.
   *
   * @param time
   * @param world
   * @return true
   * @return false
   */
  bool tick(sf::Time time, World &world) override;

  void takeDamage(float damage) override;

protected:
  /**
   * @brief Stores the type for collision checking and drawing.
   *
   */
  char type{'B'};
};
