#pragma once
#include "../common.h"
#include "../entity/entity.h"
#include <SFML/System/Vector2.hpp>

class BaseClass : public TexturedEntity {
public:
  
  BaseClass(sf::Vector2f center, const string &sprite) 
  : TexturedEntity(center, sprite) {}

  /**
   * @brief Destroy the Base Class object.
   * 
   */

/*   virtual float attack_melee();

  virtual float attack_ranged(); */

protected:
  /**
   * @brief Stores the health of the object.
   * 
   */
  int health;

  /**
   * @brief Stores the speed of the object. Manages the speed at 
   * which an object can move.
   * 
   */
  float speed;

  /**
   * @brief Stores the type of object. This is then used in each 
   * segment to designate where the object is to be placed on load.
   * 
   */
  char type;  

};