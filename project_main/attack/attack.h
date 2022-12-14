#pragma once
#include "../common.h"
#include "../entity/entity.h"
#include "../hostile/hostile.h"
#include "../player/player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics.hpp>

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
   * @brief Renders the attack in the game world.
   *
   * @param window
   */
  void render(sf::RenderWindow &window) override;

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
   * @brief A pointer to the attacking unit to avoid friendly fire.
   *
   */
  Entity *thisAttacker{};

  char meleeDirection{};
};