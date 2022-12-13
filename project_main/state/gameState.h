#pragma once
#include "../world.h"
#include "state.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

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

  /**
   * @brief Draws all game elements.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo) override;

protected:
  sf::Sprite hpBar;

private:
  /**
   * @brief Stores the game world.
   *
   */
  World world;

  /**
   * @brief Keeps track of the player object.
   *
   */
  shared_ptr<Player> player{};
};