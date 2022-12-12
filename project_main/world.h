#pragma once
#include "common.h"
#include "entity/entity.h"
#include "player/player.h"
#include <SFML/System/Vector2.hpp>

class World {
public:
  ~World() = default;

  /**
   * @brief Updates all objects in the world.
   *
   * @param time
   */
  void tick(sf::Time time);

  /**
   * @brief Renders the world.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo);

  /**
   * @brief Adds an object - this function is safe to run while
   * the world is updating itself.
   *
   * @param object
   */
  void add(shared_ptr<Entity> object);

  /**
   * @brief Checks if something collides with 'me',
   *  which is the current object.
   *
   * @param me
   * @return vector<shared_ptr<Entity>>
   */
  vector<shared_ptr<Entity>> collidesWith(Entity &me) const;

  /**
   * @brief Fetches positions. (DEPRECATED?)
   *
   * @return const sf::Vector2f
   */
  const sf::Vector2f getCenter();

  /**
   * @brief Returns if the player is alive. (DEPRECATED?)
   *
   * @return true
   * @return false
   */
  bool isPlayerAlive();

  /**
   * @brief Clears the game board when transitioning between segments.
   *
   */
  void clear();

  /**
   * @brief When creating an enemy, increments the number of enemies
   * currently on the field.
   *
   */
  void addEnemy();

  /**
   * @brief When defeating an enemy, decrements the number of enemies
   * in order to allow the player to proceed.
   *
   */
  void removeEnemy();

  /**
   * @brief If all enemies are defeated, returns true and allows the
   * player to proceed.
   *
   * @return true
   * @return false
   */
  bool levelCleared();

private:
  /**
   * @brief This container stores all game objects.
   *
   */
  vector<shared_ptr<Entity>> objects;

  /**
   * @brief This pointer stores the player character while it exists.xs
   *
   */
  shared_ptr<Entity> playerCharacter{};

  /**
   * @brief Stores the current stage.
   *
   */
  int currentStage{};

  /**
   * @brief Tracks the number of enemies currently alive.
   *
   */
  int enemiesAlive{};
};
