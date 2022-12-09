#pragma once
#include "common.h"
#include "player/player.h"
#include "entity/entity.h"
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

  const sf::Vector2f getCenter();

private:
  /**
   * @brief This container stores all game objects.
   * 
   */
  vector<shared_ptr<Entity>> objects;

  shared_ptr<Entity> playerCharacter{};
};
