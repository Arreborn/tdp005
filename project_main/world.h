#pragma once
#include "common.h"
#include "entity/entity.h"

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

private:
  /**
   * @brief This container stores all game objects.
   * 
   */
  vector<shared_ptr<Entity>> objects;
};
