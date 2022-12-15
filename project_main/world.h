#pragma once
#include "common.h"
#include "entity/entity.h"
#include "player/player.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

/**
 * @brief This class tracks all objects in the game world, and keeps them in one
 * place to update all objects. It also enables the loading of levels using the
 * level constructor.
 *
 */
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
  vector<shared_ptr<Entity>> collidesWith(Entity &me);

  /**
   * @brief Allows an entity to detect if it's about to walk off an edge
   * in the game world.
   *
   * @param x
   * @param y
   * @return true
   * @return false
   */
  bool detectEdge(float const x, float const y);

  /**
   * @brief Fetches positions.
   *
   * @return const sf::Vector2f
   */
  const sf::Vector2f getCenter();

  /**
   * @brief Returns true if the player has won the game.
   *
   * @return true
   * @return false
   */
  bool victory();

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

  /**
   * @brief This pointer stores the player character while it exists.xs
   *
   */
  shared_ptr<Entity> playerCharacter{};

  /**
   * @brief Utilizes the level constructor to load in a new level, or generate
   * a set of levels if it hasn't been done.
   *
   * @param right
   * @param player
   */
  void getLevel(bool right, shared_ptr<Player> player);

private:
  /**
   * @brief This container stores all game objects.
   *
   */
  vector<shared_ptr<Entity>> objects;

  /**
   * @brief Stores the current stage.
   *
   */
  size_t currentStage{};

  /**
   * @brief Stores the loaded segments.
   *
   */
  vector<string> loadedSegments{};

  /**
   * @brief Keeps track of the number of completed levels to track when the
   * player has won.
   *
   */
  size_t completedLevels{};

  /**
   * @brief Tracks the number of enemies currently alive.
   *
   */
  int enemiesAlive{};
};
