#pragma once
#include "../world.h"
#include "state.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

/**
 * @brief This state is active when the game is running, and handles the main
 * update loop for the world - which is also stored within this class.
 *
 */
class GameState : public State {
public:
  /**
   * @brief Construct a new Game State object.
   *
   */
  GameState();

  /**
   * @brief Ticks all game elements.
   *
   * @param delta
   * @return shared_ptr<State>
   */
  shared_ptr<State> tick(sf::Time delta, sf::RenderWindow &window) override;

  void loadTextures();
  /**
   * @brief Draws all game elements.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo) override;

private:
  /**
   * @brief Stores the game world.
   *
   */
  World world;

  /**
   * @brief Keeps track of the player object and allows certain functions to be
   * run during the game state.
   *
   */
  shared_ptr<Player> player{};

  /**
   * @brief Sprite for the HUD health bar.
   *
   */
  sf::Sprite hpBar;

  /**
   * @brief Background sprite for the health bar.
   *
   */
  sf::Sprite hpBarBackground;

  /**
   * @brief Sprite for the background image.
   *
   */
  sf::Sprite bgBack;

  /**
   * @brief Sprite for the background image.
   *
   */
  sf::Sprite bgTree;

  /**
   * @brief Sprite for the background image.
   *
   */
  sf::Sprite bgFore;

  /**
   * @brief Sprite for the background image.
   *
   */
  sf::Sprite bgLights;
};