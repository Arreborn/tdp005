#pragma once
#include "../entity/entity.h"

/**
 * @brief This class defines and handles the player character.
 * 
 */
class Player : public Entity{
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
   * @brief Draws the player in the world.
   * 
   * @param drawTo 
   */
  void render(sf::RenderWindow &drawTo) override;

  /**
   * @brief Checks if players movement is about to escape the playing field.
   * 
   * @return true 
   * @return false 
   */
  bool borderCheck();

protected:
  int health;
  float speed;
  char type;
  bool isJumping;
  sf::Vector2f acceleration{sf::Vector2f(0, 0)};
};