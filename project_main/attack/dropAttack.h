#pragma once
#include "attack.h"

/**
 * @brief This class produces ranged attacks in the game world. These can be
 * used by both the player character and enemies.
 *
 */
class DropAttack : public Attack {
public:
  /**
   * @brief The constructor accepts the center of the unit producing the attack,
   * the damage of the attack as well as a pointer to the entity producing the
   * attack.
   *
   * @param center
   * @param damage
   * @param attacker
   */
  DropAttack(sf::Vector2f center, float const damage,
             shared_ptr<Entity> attacker);

  /**
   * @brief General tick function to remove the attack from the game world once
   * it's done.
   *
   * @param time
   * @param world
   * @return true
   * @return false
   */
  bool tick(sf::Time time, World &world) override;
};