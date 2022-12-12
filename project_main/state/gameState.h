#pragma once
#include "state.h"
#include "../world.h"

class GameState : public State
{
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
  shared_ptr<State> tick(sf::Time delta) override;

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
};