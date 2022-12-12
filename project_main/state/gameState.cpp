#include "gameState.h"
#include "../level/levelConstructor.h"
#include "../player/player.h"
#include "menuState.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

GameState::GameState() {
  player = std::make_shared<Player>(
      sf::Vector2f(1100, 1100)); // these coordinates are set to ensure the
                                 // player starts at the left
  world.add(player);             // adds the player object into the game world
  LevelConstructor::generateLevel(world, player); // generates a first level
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

  if (world.levelCleared() && player->hittingBorder()) {
    world.clear();
    LevelConstructor::generateLevel(world, player);
  }

  return nullptr;
}

void GameState::render(sf::RenderWindow &drawTo) {
  world.render(drawTo);
  drawTo.setView(view);
};