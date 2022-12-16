#pragma once
#include "../common.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief This state represents the larger state of the game, for instance
 * if a menu is active, or if the game is running.
 *
 */
class State : public std::enable_shared_from_this<State> {
public:
  /**
   * @brief Construct a new State object.
   *
   */
  State();

  /**
   * @brief Destroy the State object.
   *
   */
  virtual ~State();

  /**
   * @brief Runs when a key is pressed down.
   *
   * @param key
   */
  virtual void keyPress(sf::Keyboard::Key key);

  /**
   * @brief Runs when a key is released.
   *
   * @param key
   */
  virtual void keyRelease(sf::Keyboard::Key key);

  /**
   * @brief Tick is called before each screen refresh, and may
   * switch states.
   *
   * @param time
   * @return shared_ptr<State>
   */
  virtual shared_ptr<State> tick(sf::Time time, sf::RenderWindow &window) = 0;

  /**
   * @brief This function is called to draw the screen.
   *
   * @param to
   */
  virtual void render(sf::RenderWindow &to) = 0;

  /**
   * @brief Runs a state and handles state-switches until competion.
   *
   * @param window
   * @param state
   */
  static void run(sf::RenderWindow &window, shared_ptr<State> state);

  /**
   * @brief In order to facilitate a game over-state, this function allows any
   * state to check if the players health reaches zero. Placed in the base
   * state-class to facilitate easier access between GameState and MenuState.
   *
   * @return true
   * @return false
   */
  bool isGameOver();

  /**
   * @brief This function checks whether the player has won. Placed in the base
   * state-class to facilitate easier access between GameState and MenuState.
   *
   * @return true
   * @return false
   */
  bool victoryState();

protected:
  /**
   * @brief This variable tracks the current viewport to enable zooming in and
   * out depending on the current state.
   *
   */
  sf::View view{};

  /**
   * @brief Tracks whether the game is over or not.
   *
   */
  bool gameOver{};

  /**
   * @brief Tracks whether the player has won or not.
   *
   */
  bool victory{};
};

/**
 * @brief Special state that indicates the game should exit.
 *
 */
class ExitState : public State {
public:
  /**
   * @brief Mandatory tick override.
   *
   * @param window
   * @return shared_ptr<State>
   */
  shared_ptr<State> tick(sf::Time, sf::RenderWindow &window);

  /**
   * @brief Mandatory render override.
   *
   */
  void render(sf::RenderWindow &) {}
};