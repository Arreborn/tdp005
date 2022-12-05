#pragma once
#include "../common.h"
#include "../components/component.h"

/**
 * @brief This is a general base class handling the creation of
 * block-objects.
 * 
 */
class Block : public BaseClass {
public:
  /**
   * @brief Construct a new Block object.
   * 
   * @param center 
   */
  Block(sf::Vector2f center); // maybe top left corner for easier drawing?
  
  /**
   * @brief Handles updates for collision checking.
   * 
   * @param time 
   * @param world 
   * @return true 
   * @return false 
   */
  bool tick(sf::Time time, World &world) override;

  /**
   * @brief Renders the object in the provided window.
   * 
   * @param drawTo 
   */
  void render(sf::RenderWindow &drawTo) override;

protected:

  /**
   * @brief Stores the type for collision checking and drawing.
   * 
   */
  char type{'B'};
};
