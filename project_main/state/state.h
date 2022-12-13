#pragma once
#include "../common.h"

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
  virtual shared_ptr<State> tick(sf::Time time) = 0;

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

  bool isGameOver();

protected:
  sf::View view{};
  bool gameOver{};
};

/**
 * @brief Special state that indicates the game should exit.
 *
 */
class ExitState : public State {
public:
  shared_ptr<State> tick(sf::Time);
  void render(sf::RenderWindow &) {}
};