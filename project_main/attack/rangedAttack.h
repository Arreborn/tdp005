#pragma once
#include "attack.h"

/**
 * @brief This class produces ranged attacks in the game world. These can be
 * used by both the player character and enemies.
 *
 */
class RangedAttack : public Attack {
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
  RangedAttack(sf::Vector2f center, float const damage,
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

  /**
   * @brief Override for takeDamage. Will not be used by this entity.
   *
   * @param damage
   */
  void takeDamage(float damage) override;

protected:
  /**
   * @brief The direction of this attack.
   *
   */
  char attackDirection{};

  /**
   * @brief This integer tracks the current animation frame for this object.
   *
   */
  int animation{1};

  /**
   * @brief Every tick, this is incremented by one, in order to facilitate a
   * smooth but fast animation for the object.
   *
   */
  int tickCount{};
};