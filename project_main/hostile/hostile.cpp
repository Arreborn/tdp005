#include "hostile.h"
#include "../staticEntity/block.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Hostile::Hostile(sf::Vector2f center) 
  : Entity(center, "sprites/mushy_test.png", 'h'), health{100}, speed(5.0){
    sprite.setOrigin(0, 0);
  }

bool Hostile::tick(sf::Time, World &){ 

  // movement and behaviour

  if (!isAlive()){
    // death animation
  }

  return true;
 };

void Hostile::render(sf::RenderWindow &drawTo){
  Entity::render(drawTo);
}

bool Hostile::isAlive(){
  if (health <= 0){
    return false;
  } else {
    return true;
  }
}
