#include "gameState.h"
#include "../level/levelConstructor.h"
#include "../player/player.h"
#include "../sprites/spriteManager.h"
#include "menuState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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

shared_ptr<State> GameState::tick(sf::Time time, sf::RenderWindow &window) {
  int curr{};
  if (player->damageTaken()) {
    if (player->getHealth() % 2 == 0) {
      curr = ((player->getHealth() / 2) * 9 + ((player->getHealth() / 2)) * 3);
      hpBar.setTextureRect(sf::IntRect(0, 0, curr, 8));
    } else {
      curr = ((player->getHealth() - 1) / 2) * 9 + 5 +
             (((player->getHealth() + 1) / 2) - 1) * 3;
      hpBar.setTextureRect(sf::IntRect(0, 0, curr, 8));
    }
  }

  gameOver = !player->isAlive();

  // zooms camera when in gamestate
  // sf::Vector2f hpPos{world.getCenter()};
  // hpBar.setOrigin(hpPos.x + 100.0f, hpPos.y + 400.0f);
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

  if (world.levelCleared() && player->hittingBorder()) {
    world.clear();
    LevelConstructor::generateLevel(world, player);
  }

  if (gameOver) {
    // resets viewport
    view.setCenter(640.0f, 400.0f);
    view.setSize(1280.0, 800.0);
    window.setView(view);
    return std::make_shared<MenuState>(shared_from_this());
  } else {
    return nullptr;
  }
}

void GameState::render(sf::RenderWindow &drawTo) {
  world.render(drawTo);
  drawTo.setView(view);
  hpBar.setPosition(sf::Vector2f(640.0f, 400.0f));
  drawTo.draw(hpBar);
};
