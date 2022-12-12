#include "gameState.h"
#include "../level/levelConstructor.h"
#include "../player/player.h"
#include "../sprites/spriteManager.h"
#include "menuState.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

GameState::GameState()
{
  sf::Texture *t = SpriteManager::get("sprites/Healthbar.png");
  auto size = t->getSize();
  hpBar.setTexture(*t);
  hpBar.setOrigin(size.x, size.y / 2.0f);

  player = std::make_shared<Player>(sf::Vector2f(1100, 1100)); // these coordinates are set to ensure the player starts at the left
  world.add(player);                                           // adds the player object into the game world
  LevelConstructor::generateLevel(world, player);              // generates a first level
}

shared_ptr<State> GameState::tick(sf::Time time)
{
  if (player.isHit)
  {
    hpBar.setTextureRect(sf::IntRect(0, 0, 54, 8));
  }

  // zooms camera when in gamestate
  view.setCenter(world.getCenter());
  view.setSize(640.0f, 400.0f);
  world.tick(time);

  // Checks for pause
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    // resets viewport
    view.setCenter(640.0f, 400.0f);
    view.setSize(1280.0, 800.0);
    return std::make_shared<MenuState>(shared_from_this());
  }

  if (!world.isPlayerAlive())
  {
    // return GameOverState ptr
  }
  if (world.levelCleared() && player->hittingBorder())
  {
    world.clear();
    LevelConstructor::generateLevel(world, player);
  }

  return nullptr;
}

void GameState::render(sf::RenderWindow &drawTo)
{
  world.render(drawTo);
  drawTo.setView(view);
  hpBar.setPosition(sf::Vector2f(640.0f, 400.0f));
  drawTo.draw(hpBar);
};
