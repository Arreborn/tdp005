#include "gameState.h"
#include "menuState.h"
#include "../level/levelConstructor.h"
#include "../player/player.h"
#include <SFML/System/Vector2.hpp>

GameState::GameState() {
  LevelConstructor::generateLevel(world);
  world.add(std::make_shared<Player>(sf::Vector2f(width / 2.0, height / 2.0)));
}

shared_ptr<State> GameState::tick(sf::Time time) {
  world.tick(time);

  // Checks for pause
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
    return std::make_shared<MenuState>(shared_from_this());
  }
  return nullptr;
}

void GameState::render(sf::RenderWindow &drawTo){
  world.render(drawTo);
};