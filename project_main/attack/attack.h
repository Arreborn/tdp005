#pragma once
#include "../common.h"
#include "../entity/entity.h"
#include "../hostile/hostile.h"
#include "../player/player.h"
#include "../staticEntity/block.h"
#include "../world.h"

/**
 * @brief This class produces general attacks in the game world. These will be
 * used by both the player character and enemies.
 *
 */
class Attack : public Entity {
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
  Attack(sf::Vector2f center, float const damage, shared_ptr<Entity> attacker);

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
   * @brief Stores the damage of the attack while the object lives.
   *
   */
  float damage{};

  /**
   * @brief The duration of the attack.
   *
   */
  sf::Time attackDuration{};

  /**
   * @brief A pointer to the attacking unit to check its type and avoid friendly
   * fire.
   *
   */
  Entity *thisAttacker{};

  /**
   * @brief In order to allow the attack to face different directions, this char
   * stores the current direction the attack will be facing no matter where the
   * attacker faces.
   *
   */
  char meleeDirection{};
};