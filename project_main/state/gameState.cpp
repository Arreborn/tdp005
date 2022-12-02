#include "gameState.h"
#include "menuState.h"

shared_ptr<State> GameState::tick(sf::Time time) {
  // here the basic file created enemies

  world.tick(time);

  // Checks for pause
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
    return std::make_shared<MenuState>(shared_from_this()); // why you no work
  }
  return nullptr;
}

void GameState::render(sf::RenderWindow &drawTo){
  world.render(drawTo);
};