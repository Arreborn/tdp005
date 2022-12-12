#include "gameState.h"
#include "../level/levelConstructor.h"
#include "../player/player.h"
#include "menuState.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

GameState::GameState() {
  LevelConstructor::generateLevel(world);
  auto player{std::make_shared<Player>(sf::Vector2f(width / 2.0, height / 2.0))};
  world.add(player);
}

shared_ptr<State> GameState::tick(sf::Time time) {
  // zooms camera when in gamestate
  view.setCenter(world.getCenter());
  view.setSize(640.0f, 400.0f);
  world.tick(time);
  

  // Checks for pause
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    // resets viewport
    view.setCenter(640.0f, 400.0f);
    view.setSize(1280.0, 800.0);
    return std::make_shared<MenuState>(shared_from_this());
  }

  if (!world.isPlayerAlive()) {
    // return GameOverState ptr
  }

  return nullptr;
}

void GameState::render(sf::RenderWindow &drawTo) {
  world.render(drawTo);
  drawTo.setView(view);
};