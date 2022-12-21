#pragma once
#include "../entity/entity.h"

/**
 * @brief This class defines and handles the player character.
 *
 */
class Player : public Entity {
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
   * @brief Function used to enable a dash.
   *
   * @return float
   */
  float dash();

  /**
   * @brief Manages the players vertical position in the game world.
   *
   * @return sf::Vector2f
   */
  sf::Vector2f verticalPosition();

  /**
   * @brief Manages the players horizontal position in the game world.
   *
   * @param time
   * @return sf::Vector2f
   */
  sf::Vector2f horizontalPosition(sf::Time const &time);

  /**
   * @brief Checks if the player is alive. Used to enter game over-state.
   *
   * @return true
   * @return false
   */
  bool isAlive() override;

  /**
   * @brief Basic attack for the player. Draws a new attack-object in the world.
   *
   * @param world
   */
  void attack(World &world);

  /**
   * @brief Allows the player to take damage.
   *
   * @param damage
   */
  void takeDamage(float damage) override;

  /**
   * @brief Returns a shared pointer to the player. Used when attacking.
   *
   * @return shared_ptr<Entity>
   */

  /**
   * @brief Setter for player position. Used when contructing levels.
   *
   * @param x
   * @param y
   */
  void set(int x, int y);

  /**
   * @brief Checks if the player is hitting a border. Prevents the player from
   * moving to the next segment before killing all enemies.
   *
   * @return true
   * @return false
   */
  bool hittingBorder();

  /**
   * @brief Returns the players current health. Allows states to check current
   * health for the HUD as well as checking of the player has died.
   *
   * @return int
   */
  int getHealth();

  /**
   * @brief Heals the player a small amount when passing between segments.
   *
   */
  void heal();

protected:
  /**
   * @brief Player health. Always decreases by one when hit.
   *
   */
  int health{};

  /**
   * @brief Triggers invincibility-frames for the player after being hit.
   *
   */
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
   * be thrown away from said enemy..
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

  /**
   * @brief Stores a cooldown for the attack, to prevent spamming attacks.
   *
   */
  sf::Time attackCooldown{};

  /**
   * @brief Stores the time the player will be invincible after being hit.
   *
   */
  sf::Time iFrame{};

  /**
   * @brief Stores if the player is at the border of the screen.
   *
   */
  bool atBorder{};

  /**
   * @brief This bool enables player blinking during invincibility.
   *
   */
  bool blink{};
};